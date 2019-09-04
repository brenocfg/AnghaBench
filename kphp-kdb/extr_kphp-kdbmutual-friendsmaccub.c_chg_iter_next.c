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
struct TYPE_4__ {int i; size_t stack_top; int /*<<< orphan*/ * stack_state; int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ chg_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  chg_upd (TYPE_1__*) ; 

void chg_iter_next (chg_iterator *it) {
  if (it->x == NULL) {
    return;
  } else if (it->i == -1) {
    it->stack_state[it->stack_top]++;
    chg_upd (it);
  } else {
    // bugs, bugs, bugs...
    it->i++;
  }

}