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
struct bitwriter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bwrite_interpolative_encode_value (struct bitwriter*,int const,int const) ; 

void bwrite_interpolative_sublist (struct bitwriter *bw, int *L, int u, int v) {
  if (v - u <= 1) { return; }
  const int  m = (u + v) >> 1,
            hi = L[v] - (v - m),
            lo = L[u] + (m - u),
             a = L[m] - lo,
             r = hi - lo + 1;
  bwrite_interpolative_encode_value (bw, a, r);
  bwrite_interpolative_sublist (bw, L, u, m);
  bwrite_interpolative_sublist (bw, L, m, v);
}