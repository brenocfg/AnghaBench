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
 int stub1 (void const*,void const*,void*) ; 

void *hc_bsearch_r (const void *key, const void *base, size_t nmemb, size_t size, int (*compar) (const void *, const void *, void *), void *arg)
{
  for (size_t l = 0, r = nmemb; r; r >>= 1)
  {
    const size_t m = r >> 1;

    const size_t c = l + m;

    const char *next = (const char *) base + (c * size);

    const int cmp = (*compar) (key, next, arg);

    if (cmp > 0)
    {
      l += m + 1;

      r--;
    }

    if (cmp == 0) return ((void *) next);
  }

  return (NULL);
}