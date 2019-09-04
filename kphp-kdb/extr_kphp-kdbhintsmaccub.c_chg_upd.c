#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* trp_node_ptr ;
struct TYPE_5__ {int stack_top; int* stack_state; TYPE_1__** stack_ptr; } ;
typedef  TYPE_2__ chg_iterator ;
struct TYPE_4__ {struct TYPE_4__* r; struct TYPE_4__* l; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void chg_upd (chg_iterator *it) {
  int t = it->stack_top;
  trp_node_ptr *stack_ptr = it->stack_ptr;
  int *stack_state = it->stack_state;

  int f = 1;
  while (f) {
    if (t < 0) {
      break;
    }
    switch (it->stack_state[t]) {
    case 0:
      stack_state[t]++;
      if (stack_ptr[t]->l != NULL) {
        stack_ptr[t + 1] = stack_ptr[t]->l;
        stack_state[t + 1] = 0;
        t++;
        break;
      }
    case 1:
      f = 0;
      break;
    case 2:
      stack_state[t]++;
      if (stack_ptr[t]->r != NULL) {
        stack_ptr[t + 1] = stack_ptr[t]->r;
        stack_state[t + 1] = 0;
        t++;
        break;
      }
    case 3:
      t--;
      break;
    default:
      assert (0);
      break;
    }
  }
  it->stack_top = t;
}