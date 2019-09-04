#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cache_uri {int dummy; } ;
struct TYPE_8__ {struct cache_uri** H; } ;
struct TYPE_7__ {struct cache_uri** H; } ;
struct TYPE_6__ {long long const download_speed; long long const disk_size; } ;
struct TYPE_5__ {size_t max_retrieved_files_between_two_priority_requests; int max_erased_files_between_two_priority_requests; int /*<<< orphan*/  priority_lists_requests; } ;

/* Variables and functions */
 long long INT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cache_add (struct cache_uri*,int const) ; 
 double cache_get_uri_heuristic (struct cache_uri*) ; 
 long long cache_get_uri_size (struct cache_uri*,int) ; 
 int /*<<< orphan*/  cache_remove (struct cache_uri*,int const) ; 
 long long cached_bytes ; 
 int cached_ptr ; 
 TYPE_4__ heap_cached ; 
 int heap_cached_files ; 
 TYPE_3__ heap_uncached ; 
 size_t heap_uncached_files ; 
 long long next_download_file_time ; 
 long long next_priority_lists_request_time ; 
 int /*<<< orphan*/  resend_priority_lists_request (int const) ; 
 TYPE_2__ simulation_params ; 
 TYPE_1__ simulation_stats ; 
 size_t uncached_ptr ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long) ; 

__attribute__((used)) static void cache_download_next_file (void) {
  if (!simulation_stats.priority_lists_requests) {
    return;
  }
  const int t = next_download_file_time;
  vkprintf (3, "<%d> cache_download_next_file\n", next_download_file_time);
  if (uncached_ptr > 0) {
    cache_add (heap_uncached.H[uncached_ptr], t);
  }
  if (simulation_stats.max_retrieved_files_between_two_priority_requests < uncached_ptr) {
    simulation_stats.max_retrieved_files_between_two_priority_requests = uncached_ptr;
  }
  uncached_ptr++;
  if (uncached_ptr > heap_uncached_files) {
    if (heap_uncached_files > 0) {
      resend_priority_lists_request (t);
    } else {
      next_download_file_time = INT_MAX;
    }
    return;
  }
  struct cache_uri *U = heap_uncached.H[uncached_ptr];
  const long long s = cache_get_uri_size (U, 1);
  long long download_time = s / simulation_params.download_speed;
  if (s % simulation_params.download_speed) {
    download_time++;
  }
  assert (download_time + next_download_file_time <= INT_MAX);
  next_download_file_time += download_time;
  if (next_download_file_time >= next_priority_lists_request_time) {
    return;
  }

  long long min_cache_bytes = simulation_params.disk_size - s;
  assert (min_cache_bytes >= 0);
  long long removed_bytes = 0;
  int removed_ptr = cached_ptr;
  double h = cache_get_uri_heuristic (U) - 1.0;
  while (cached_bytes - removed_bytes > min_cache_bytes && removed_ptr <= heap_cached_files) {
    if (cache_get_uri_heuristic ((struct cache_uri *) heap_cached.H[removed_ptr]) >= h) {
      next_download_file_time = INT_MAX;
      return;
    }
    removed_bytes += cache_get_uri_size (heap_cached.H[removed_ptr], 1);
    removed_ptr++;
  }

  if (cached_bytes - removed_bytes > min_cache_bytes && removed_ptr > heap_cached_files) {
    resend_priority_lists_request (t);
    return;
  }

  while (cached_ptr < removed_ptr) {
    cache_remove (heap_cached.H[cached_ptr++], t);
  }

  if (simulation_stats.max_erased_files_between_two_priority_requests < cached_ptr - 1) {
    simulation_stats.max_erased_files_between_two_priority_requests = cached_ptr - 1;
  }
}