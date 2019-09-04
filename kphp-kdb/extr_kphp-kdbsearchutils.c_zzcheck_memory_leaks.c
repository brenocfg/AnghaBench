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

void zzcheck_memory_leaks (void) {
  #ifdef DEBUG_ZZMALLOC
  if (size_sum_zzmallocs != size_sum_zzfree ||
      tot_calls_zzmallocs != tot_calls_zzfree) {
    fprintf (stderr, "size_sum_zzmallocs = %lld\n"
                     "size_sum_zzfree = %lld\n"
                     "tot_calls_zzmallocs = %lld\n"
                     "tot_calls_zzfree = %lld\n",
                     size_sum_zzmallocs, size_sum_zzfree,
                     tot_calls_zzmallocs, tot_calls_zzfree);
    assert (0);
    }
  #endif
}