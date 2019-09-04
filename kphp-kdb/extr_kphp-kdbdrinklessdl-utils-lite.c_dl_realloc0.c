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
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ predict_malloc_memory (size_t) ; 
 void* realloc (void*,size_t) ; 

void *dl_realloc0 (void *p, size_t x, size_t old) {
  dl_memory_used += predict_malloc_memory (x) - predict_malloc_memory (old);

#ifdef DL_DEBUG_MEM
  MEM_POS
  void *res = realloc (p, x);
  if (res != NULL && x > old) {
    memset ((char *)res + old, 0, x - old);
  }

  fprintf (stderr, "r\t%lld\t%lld\t%p\t%p\n", (long long)old, (long long)x, p, res);
  return res;
#else
  void *new_p = realloc (p, x);
  if (new_p != NULL && x > old) {
    memset ((char *)new_p + old, 0, x - old);
  }

  return new_p;
#endif
}