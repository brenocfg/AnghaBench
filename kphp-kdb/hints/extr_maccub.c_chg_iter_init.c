#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ treap ;
struct TYPE_6__ {scalar_t__* x; int i; scalar_t__* stack_state; int /*<<< orphan*/ * stack_ptr; scalar_t__ stack_top; } ;
typedef  TYPE_2__ chg_iterator ;
typedef  scalar_t__* changes ;

/* Variables and functions */
 int /*<<< orphan*/  chg_upd (TYPE_2__*) ; 

void chg_iter_init (chg_iterator *it, changes x) {
  it->x = x;

#ifdef __x86_64__
  if ((long)x < 0) {
    it->i = 0;
  } else
#endif
  if (x) {
    if (x[0] > 0) {
      it->i = 0;
    } else {
      it->i = -1;
      it->stack_top = 0;
      it->stack_ptr[0] = ((treap *)(x))->root;
      it->stack_state[0] = 0;

      chg_upd (it);
    }
  }
}