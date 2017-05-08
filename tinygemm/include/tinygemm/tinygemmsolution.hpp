#ifndef TINYGEMMSOLUTION_HPP
#define TINYGEMMSOLUTION_HPP


#include <string> 
#include <map>
#include <chrono>

#include <tinygemm/tinygemmgeometry.hpp>
#include <tinygemm/hyperparams.hpp>
#include <tinygemm/derivedparams.hpp>
#include <tinygemm/kernelstring.hpp>


namespace tinygemm{

class TinyGemmSolutionStatistics{
  public:
    /* the median time and flop/s recorded with the(se) kernel(s) on the specified benchmarked problem */
    float median_benchmark_time;
    float median_benchmark_gflops;

    /* the time in seconds at which this solution was discovered  (from start of descent)  */
    float solution_discovery_time;
    
    /* timestamp (date) when found */
    std::string date;
    
    TinyGemmSolutionStatistics(float median_benchmark_time, float median_benchmark_gflops, float solution_discovery_time, std::string date);
    TinyGemmSolutionStatistics(std::string cache_string);

    std::string get_string(){
      std::stringstream ss;
      ss << "runtime_" << median_benchmark_time << "__gflops_" << median_benchmark_gflops << "__date_" << date;
      return ss.str();
    }

};

/* Note 01 feb 2017: A TinyGemmSolution is only valid for a fixed geometry */
class TinyGemmSolution{

public:

  /* the geometry on which this solution was obtained */
  tinygemm::TinyGemmGeometry geometry;

  TinyGemmSolutionStatistics statistics;
  
  /* the kernels of which the solution is comprised */
  std::vector<KernelString> v_tgks;

  std::string hyper_param_string;

  TinyGemmSolution(const tinygemm::TinyGemmGeometry & geometry_, TinyGemmSolutionStatistics tgss_, const std::vector<KernelString> & v_tgks_, std::string hyper_param_string_): geometry(geometry_), statistics(tgss_), v_tgks(v_tgks_), hyper_param_string(hyper_param_string_) {}

  /* return a string summarising the TinyGemmGeometry, less offsets (a request from MLOpen) */
  std::string get_networkconfig_string() const;

  /* return a string describing the hyper parameters */
  std::string get_hyper_param_string() const;
  

};

}

#endif
