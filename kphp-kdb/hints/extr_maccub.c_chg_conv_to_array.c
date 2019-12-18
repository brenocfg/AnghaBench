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
typedef  scalar_t__* changes ;

/* Variables and functions */
 int trp_conv_to_array_rev (int /*<<< orphan*/ ,int*) ; 

int chg_conv_to_array (changes x, int *res) {
#ifdef __x86_64__
  if ((long)(x) < 0) {
    res[0] = -(long)(x);
    return 1;
  } else
#endif
  if (x) {
    if (x[0] > 0) {
      int i, n;
      for (n = x[0]; !x[n]; n--) ;
      for (i = n; i >= 1; i--) {
        *res++ = x[i];
      }
      return n;
    } else {
      return trp_conv_to_array_rev (*(treap *)(x), res);
    }
  }
  return 0;
}