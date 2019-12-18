#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* lcp; int n; } ;
typedef  TYPE_1__ suffix_array_t ;

/* Variables and functions */

__attribute__((used)) static int lcp_table (suffix_array_t *A, int d, int f) {
  if (d + 1 == f) { return A->lcp[f]; }
  int i = (d + f) >> 1, *r = A->lcp + (A->n + 1 + i);
  if (*r >= 0) { return *r; }
  int r1 = lcp_table (A, d, i), r2 = lcp_table (A, i, f);
  return *r = (r1 < r2) ? r1 : r2;
}