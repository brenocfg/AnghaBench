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
struct TYPE_3__ {int /*<<< orphan*/  rhs; int /*<<< orphan*/  lhs; } ;
typedef  TYPE_1__ predicate_logical ;
typedef  int /*<<< orphan*/  actual_object ;

/* Variables and functions */
 scalar_t__ DL_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eval ; 

int predicate_logical_eval_or (predicate_logical *self, actual_object *ao) {
  return DL_CALL (self->lhs, eval, ao) || DL_CALL (self->rhs, eval, ao);
}