#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* x; int i; } ;
typedef  TYPE_1__ blist_iterator ;
typedef  int* blist ;

/* Variables and functions */
 int /*<<< orphan*/  blist_iter_next (TYPE_1__*) ; 

void blist_iter_init (blist_iterator *it, blist x, int tot_items, int len, int nr) {
  it->x = x;

  int n;

  if (x == NULL) {
    n = 0;
  } else {
    n = it->x[0];
  }

  int l = 0, r = n + 1;

  while (l + 1 < r) {
    int c = (l + r) >> 1;
    if (it->x[c] <= nr) {
      r = c;
    } else {
      l = c;
    }
  }
  it->i = r - 1;
  blist_iter_next (it);
}