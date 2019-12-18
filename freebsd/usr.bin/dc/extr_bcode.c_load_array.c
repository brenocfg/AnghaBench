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
typedef  int /*<<< orphan*/  u_long ;
struct value {scalar_t__ type; } ;
struct stack {int dummy; } ;
struct number {int /*<<< orphan*/  number; } ;
struct TYPE_2__ {struct stack* reg; } ;

/* Variables and functions */
 scalar_t__ BCODE_NONE ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_ARRAY_INDEX ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 struct value* frame_retrieve (struct stack*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_number (struct number*) ; 
 int /*<<< orphan*/  get_ulong (struct number*) ; 
 struct number* new_number () ; 
 struct number* pop_number () ; 
 int /*<<< orphan*/  push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_number (struct number*) ; 
 int readreg () ; 
 int /*<<< orphan*/  stack_dup_value (struct value*,struct value*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
load_array(void)
{
	struct number *inumber, *n;
	struct stack *stack;
	struct value *v;
	struct value copy;
	u_long idx;
	int reg;

	reg = readreg();
	if (reg >= 0) {
		inumber = pop_number();
		if (inumber == NULL)
			return;
		idx = get_ulong(inumber);
		if (BN_is_negative(inumber->number))
			warnx("negative idx");
		else if (idx == ULONG_MAX || idx > MAX_ARRAY_INDEX)
			warnx("idx too big");
		else {
			stack = &bmachine.reg[reg];
			v = frame_retrieve(stack, idx);
			if (v == NULL || v->type == BCODE_NONE) {
				n = new_number();
				bn_check(BN_zero(n->number));
				push_number(n);
			}
			else
				push(stack_dup_value(v, &copy));
		}
		free_number(inumber);
	}
}