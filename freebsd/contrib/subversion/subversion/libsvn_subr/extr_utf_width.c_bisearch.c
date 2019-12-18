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
struct interval {scalar_t__ first; scalar_t__ last; } ;
typedef  scalar_t__ apr_uint32_t ;

/* Variables and functions */

__attribute__((used)) static int
bisearch(apr_uint32_t ucs, const struct interval *table, apr_uint32_t max)
{
  apr_uint32_t min = 0;
  apr_uint32_t mid;

  if (ucs < table[0].first || ucs > table[max].last)
    return 0;
  while (max >= min) {
    mid = (min + max) / 2;
    if (ucs > table[mid].last)
      min = mid + 1;
    else if (ucs < table[mid].first)
      max = mid - 1; /* this is safe because ucs >= table[0].first */
    else
      return 1;
  }

  return 0;
}