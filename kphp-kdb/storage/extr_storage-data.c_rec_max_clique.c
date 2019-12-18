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

__attribute__((used)) static void rec_max_clique (int n, int *a, int k, int st, int sz, int *res, int *best) {
  int i;
  if (k == n) {
    if (sz < *res) {
      *res = sz;
      *best = st;
    }
    return;
  }
  rec_max_clique (n, a, k + 1, st, sz, res, best);
  for (i = 0; i < k; i++) {
    if (((1 << i) & st) && !(a[i] & (1 << k))) {
      return;
    }
  }
  rec_max_clique (n, a, k + 1, st | (1 << k), sz + 1, res, best);
}