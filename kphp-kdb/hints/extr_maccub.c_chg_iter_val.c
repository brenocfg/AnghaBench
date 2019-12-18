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
struct TYPE_5__ {int* x; int i; size_t stack_top; TYPE_1__** stack_ptr; } ;
typedef  TYPE_2__ chg_iterator ;
struct TYPE_4__ {int x; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int chg_iter_val (chg_iterator *it) {
  if (it->x == NULL) {
    return 0;
  } else if (it->i == -1) {
    if (it->stack_top >= 0) {
      return it->stack_ptr[it->stack_top]->x;
    } else {
      return 0;
    }
  } else
#ifdef __x86_64__
  if ((long)it->x < 0) {
    if (it->i == 0) {
      return -(long)it->x;
    } else {
      return 0;
    }
  } else
#endif
  if (it->x) { // TODO optimize
    if (it->i < it->x[0]) {
      return it->x[it->i + 1];
    } else {
      return 0;
    }
  }

  assert (0);
  return 0;
}