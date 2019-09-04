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
struct TYPE_4__ {int top; int val; int* l; int* r; int* n; int* st; int* s_val; } ;
typedef  TYPE_1__ iCode_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int iCode_get_next_int (TYPE_1__*,int) ; 

void iCode_iter_next (iCode_iterator *it) {
  if (it->top == -1) {
    it->val = 0;
    return;
  }

  int *l = it->l, *r = it->r, *n = it->n, t = it->top, *st = it->st, *val = it->s_val;

  int f = 1, x, c;
  while (f) {
    switch (st[t]) {
    case 0:
      x = iCode_get_next_int (it, l[t] - r[t] - n[t] + 1), c = n[t] / 2;
      val[t] = l[t] - c - x;
      st[t] = 1;
      if (c) {
        l[t + 1] = l[t];
        r[t + 1] = val[t];
        n[t + 1] = c;
        st[++t] = 0;
      }
      break;

    case 1:
      it->val = val[t];
      st[t] = 2;
      f = 0;
      break;

    case 2:
      st[t] = 3;
      if (n[t] > 2) {
        l[t + 1] = val[t] - 1;
        r[t + 1] = r[t];
        n[t + 1] = n[t] - n[t] / 2 - 1;
        st[++t] = 0;
      }
      break;

    case 3:
      t--;
      break;

    default: // TODO optimize
      assert (0);
    }
    if (t < 0) {
      it->val = 0;
      f = 0;
    }
  }
  it->top = t;
}