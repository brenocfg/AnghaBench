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
struct TYPE_3__ {int* x; } ;
typedef  TYPE_1__ blist_iterator ;

/* Variables and functions */

int blist_iter_has (blist_iterator *it, int val) {
  if (it->x == NULL) {
    return 0;
  }

  int n = it->x[0];

  if (n <= 8) {
    int i;
    for (i = 1; i <= n; i++) {
      if (it->x[i] == val) {
        return 1;
      }
    }
    return 0;
  } else {
    int l = 1, r = n + 1, c;
    while (l + 1 < r) {
      c = (l + r) / 2;
      if (it->x[c] >= val) {
        l = c;
      } else {
        r = c;
      }
    }
    return it->x[l] == val;
  }
}