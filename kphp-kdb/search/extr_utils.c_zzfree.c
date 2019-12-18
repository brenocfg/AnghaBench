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
 int MAX_ZALLOC ; 
 int /*<<< orphan*/  free (void*) ; 
 int size_sum_zzfree ; 
 int /*<<< orphan*/  tot_calls_zzfree ; 
 int total_memory_used ; 
 int /*<<< orphan*/  zfree (void*,int) ; 

void zzfree (void *src, int size) {
  if (!src) { return; }
  #ifdef DEBUG_ZZMALLOC
  size_sum_zzfree += size;
  tot_calls_zzfree++;
  #endif
  if (size < MAX_ZALLOC) {
    zfree (src, size);
  } else {
    total_memory_used -= size;
    free (src);
  }
}