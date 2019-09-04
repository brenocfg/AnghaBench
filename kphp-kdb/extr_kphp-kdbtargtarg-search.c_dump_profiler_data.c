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

/* Variables and functions */
 long PROFILERS_NUM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__* profiler ; 
 int* profiler_cnt ; 
 int /*<<< orphan*/  stderr ; 
 int tot_queries ; 
 int tot_queries_time ; 
 int tot_users ; 

void dump_profiler_data (void) {
  long i, j = PROFILERS_NUM;
  while (j > 0 && !profiler_cnt[j-1]) {
    j--;
  }
  fprintf (stderr, "%d queries performed in %.6f seconds, %.6f average; tot_users=%d\n", tot_queries, tot_queries_time, tot_queries ? tot_queries_time / tot_queries : 0, tot_users);
  for (i = 0; i < j; i++) {
    fprintf (stderr, "%ld:%llu/%llu=%.0f ", i, profiler[i], profiler_cnt[i], profiler_cnt[i] ? (double) profiler[i] / profiler_cnt[i] : 0.0);
  }
  fprintf (stderr, "\n");
}