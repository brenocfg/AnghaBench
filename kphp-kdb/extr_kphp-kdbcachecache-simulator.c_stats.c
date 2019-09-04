#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {long long cache_hits_bytes; long long download_bytes; int with_known_size_files; long long with_known_size_bytes; long long max_known_size; int /*<<< orphan*/  resource_usage_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_STAT_FILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_STAT_I32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_STAT_I64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_STAT_TIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_all_uri_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_hits ; 
 int /*<<< orphan*/  cache_init ; 
 int /*<<< orphan*/  cache_misses ; 
 int /*<<< orphan*/  cgsl_order_top ; 
 int /*<<< orphan*/  download ; 
 int /*<<< orphan*/  erased ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_rusage_time () ; 
 char* human_readable_size (long long const) ; 
 int /*<<< orphan*/  max_erased_files_between_two_priority_requests ; 
 int /*<<< orphan*/  max_priority_lists_request_time ; 
 int /*<<< orphan*/  max_retrieved_files_between_two_priority_requests ; 
 int /*<<< orphan*/  max_uries_in_one_bucket ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  print_uri ; 
 int /*<<< orphan*/  priority_lists_requests ; 
 int /*<<< orphan*/  priority_lists_requests_after_list_ending ; 
 int /*<<< orphan*/  required_files_with_unknown_size ; 
 int /*<<< orphan*/  resource_usage_time ; 
 char* safe_div (long long,long long) ; 
 TYPE_1__ simulation_stats ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uries_last_day_access ; 
 int /*<<< orphan*/  uries_last_hour_access ; 
 int /*<<< orphan*/  uries_last_month_access ; 
 int /*<<< orphan*/  uries_last_week_access ; 
 int /*<<< orphan*/  with_known_size_files ; 

__attribute__((used)) static void stats (void) {
  now = time (NULL);
  cache_all_uri_foreach (print_uri, cgsl_order_top);
  PRINT_STAT_FILE(cache_init);
  PRINT_STAT_FILE(download);
  PRINT_STAT_FILE(erased);
  PRINT_STAT_FILE(cache_hits);
  const long long difference_bytes = simulation_stats.cache_hits_bytes - simulation_stats.download_bytes;
  fprintf (stderr, "cache_hits_bytes-download_bytes\t%lld(%s)\n",
    difference_bytes, human_readable_size (difference_bytes));
  fprintf (stderr, "cache_hits_bytes/download_bytes\t%.6lf\n",
    safe_div (simulation_stats.cache_hits_bytes, simulation_stats.download_bytes));
  PRINT_STAT_FILE(cache_misses);
  PRINT_STAT_I64(priority_lists_requests);
  PRINT_STAT_I64(priority_lists_requests_after_list_ending);
  PRINT_STAT_I64(required_files_with_unknown_size);
  PRINT_STAT_I64(with_known_size_files);
  long long average_known_size = simulation_stats.with_known_size_files ? simulation_stats.with_known_size_bytes / simulation_stats.with_known_size_files : 0;
  fprintf (stderr, "average_known_size\t%s\n", human_readable_size (average_known_size));
  fprintf (stderr, "max_known_size\t%s\n", human_readable_size (simulation_stats.max_known_size));
  PRINT_STAT_I32(max_retrieved_files_between_two_priority_requests);
  PRINT_STAT_I32(max_erased_files_between_two_priority_requests);
  PRINT_STAT_TIME(max_priority_lists_request_time);
  simulation_stats.resource_usage_time = get_rusage_time ();
  PRINT_STAT_TIME(resource_usage_time);
  PRINT_STAT_I32(max_uries_in_one_bucket);
  PRINT_STAT_I32(uries_last_hour_access);
  PRINT_STAT_I32(uries_last_day_access);
  PRINT_STAT_I32(uries_last_week_access);
  PRINT_STAT_I32(uries_last_month_access);
  fflush (stderr);
}