#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  dyn_mark_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int QUERY_STATS_PERIODICITY ; 
 int /*<<< orphan*/  dump_profiler_data () ; 
 int /*<<< orphan*/  dyn_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double) ; 
 double get_utime (int /*<<< orphan*/ ) ; 
 int perform_query_internal (int) ; 
 int* profiler ; 
 int /*<<< orphan*/ * profiler_cnt ; 
 int /*<<< orphan*/  stderr ; 
 int tot_queries ; 
 double tot_queries_time ; 
 int verbosity ; 

int perform_query (int seed) {
  dyn_mark_t heap_state;
  dyn_mark (heap_state);

  double query_time = -get_utime (CLOCK_MONOTONIC);

  int res = perform_query_internal (seed);

  query_time += get_utime (CLOCK_MONOTONIC);
  if (verbosity > 1) {
    fprintf (stderr, "query performed in %.6f seconds\n", query_time);
  }

  tot_queries_time += query_time;
  tot_queries++;

  profiler_cnt[15]++;
  profiler[15] += res;

  //fprintf (stderr, "%d users for query '%s'\n", res, Qs0);  

  if (verbosity > 2 && !(tot_queries & (QUERY_STATS_PERIODICITY - 1))) {
    dump_profiler_data ();
  }

  dyn_release (heap_state);
  return res;
}