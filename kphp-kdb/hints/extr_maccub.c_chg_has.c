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
typedef  int /*<<< orphan*/  treap ;
typedef  int* changes ;

/* Variables and functions */
 int trp_has (int /*<<< orphan*/ ,int) ; 

int chg_has (changes x, int val) {
  val *= 2;

#ifdef __x86_64__
  if ((long)(x) < 0) {
    if (((-(long)(x)) & -2) == val) {
      return (-(long)(x)) & 1 ? 1 : -1;
    }
    return 0;
  } else
#endif
  if (x) {
    if (x[0] > 0) {
      int i, n = x[0];

      for (i = 1; i <= n; i++) {
        if ((x[i] & -2) == val) {
          return x[i] & 1 ? 1 : -1;
        }
      }
      return 0;
    } else {
      return trp_has (*(treap *)(x), val);
    }

  }
  return 0;
}