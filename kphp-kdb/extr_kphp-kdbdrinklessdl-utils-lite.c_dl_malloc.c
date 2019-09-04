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
 int /*<<< orphan*/  dl_memory_used ; 
 void* malloc (size_t) ; 
 scalar_t__ predict_malloc_memory (size_t) ; 

void *dl_malloc (size_t x) {
  dl_memory_used += predict_malloc_memory (x);

#ifdef DL_DEBUG_MEM
  MEM_POS
  void *res = malloc (x);
  fprintf (stderr, "a\t%lld\t%p\n", (long long)x, res);
  return res;
#else
  return malloc (x);
#endif
}