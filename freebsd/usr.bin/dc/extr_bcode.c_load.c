#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct number {int /*<<< orphan*/  number; } ;
struct TYPE_2__ {int /*<<< orphan*/ * reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ ) ; 
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 struct number* new_number () ; 
 int /*<<< orphan*/  push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_number (struct number*) ; 
 int readreg () ; 
 int /*<<< orphan*/  stack_dup_value (struct value*,struct value*) ; 
 struct value* stack_tos (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
load(void)
{
	struct number *n;
	struct value *v;
	struct value copy;
	int idx;

	idx = readreg();
	if (idx >= 0) {
		v = stack_tos(&bmachine.reg[idx]);
		if (v == NULL) {
			n = new_number();
			bn_check(BN_zero(n->number));
			push_number(n);
		} else
			push(stack_dup_value(v, &copy));
	}
}