#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ delay_between_priority_lists_requests; scalar_t__ optimization; } ;
struct TYPE_3__ {int max_erased_files_between_two_priority_requests; int max_retrieved_files_between_two_priority_requests; double max_priority_lists_request_time; int /*<<< orphan*/  priority_lists_requests; } ;

/* Variables and functions */
 int CACHE_MAX_HEAP_SIZE ; 
 int /*<<< orphan*/  cache_get_priority_heaps (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cached_ptr ; 
 double get_rusage_time () ; 
 int /*<<< orphan*/  heap_cached ; 
 int /*<<< orphan*/  heap_cached_files ; 
 int /*<<< orphan*/  heap_uncached ; 
 int /*<<< orphan*/  heap_uncached_files ; 
 int /*<<< orphan*/  next_download_file_time ; 
 int /*<<< orphan*/  next_priority_lists_request_time ; 
 TYPE_2__ simulation_params ; 
 TYPE_1__ simulation_stats ; 
 scalar_t__ uncached_ptr ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void cache_priority_lists_request (void) {
  vkprintf (3, "<%d> cache_priority_list_request\n", next_priority_lists_request_time);
  double t = -get_rusage_time ();
  int cached_limit = 0, uncached_limit = 0;
  if (simulation_params.optimization) {
    cached_limit = 2 * simulation_stats.max_erased_files_between_two_priority_requests;
    if (cached_limit > CACHE_MAX_HEAP_SIZE) {
      cached_limit = CACHE_MAX_HEAP_SIZE;
    }
    uncached_limit = 2 * simulation_stats.max_retrieved_files_between_two_priority_requests;
    if (uncached_limit > CACHE_MAX_HEAP_SIZE) {
      uncached_limit = CACHE_MAX_HEAP_SIZE;
    }
  }

  if (!cached_limit) {
    cached_limit = CACHE_MAX_HEAP_SIZE;
  }
  if (!uncached_limit) {
    uncached_limit = CACHE_MAX_HEAP_SIZE;
  }

  cache_get_priority_heaps (&heap_cached, &heap_uncached, cached_limit, uncached_limit, &heap_cached_files, &heap_uncached_files);
  vkprintf (2, "heap_cached_files: %d, heap_uncached_files: %d\n", heap_cached_files, heap_uncached_files);

  //heap_cached_all_uries = heap_cached_files < cached_limit;
  //heap_uncached_all_uries = heap_uncached_files < uncached_limit;

  t += get_rusage_time ();
  if (simulation_stats.max_priority_lists_request_time < t) {
    simulation_stats.max_priority_lists_request_time = t;
  }
  cached_ptr = 1;
  uncached_ptr = 0;
  next_download_file_time = next_priority_lists_request_time;
  next_priority_lists_request_time += simulation_params.delay_between_priority_lists_requests;
  simulation_stats.priority_lists_requests++;
}