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
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
bsearch_lower_bound(const void *key,
                    const void *base,
                    int nelts,
                    int elt_size,
                    int (*compare_func)(const void *, const void *))
{
  int lower = 0;
  int upper = nelts - 1;

  /* Binary search for the lowest position at which to insert KEY. */
  while (lower <= upper)
    {
      int try = lower + (upper - lower) / 2;  /* careful to avoid overflow */
      int cmp = compare_func((const char *)base + try * elt_size, key);

      if (cmp < 0)
        lower = try + 1;
      else
        upper = try - 1;
    }
  assert(lower == upper + 1);

  return lower;
}