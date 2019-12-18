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
struct value {int dummy; } ;
struct stack {int dummy; } ;
struct number {int /*<<< orphan*/  number; } ;
struct TYPE_2__ {struct stack* reg; } ;

/* Variables and functions */
 scalar_t__ BN_is_negative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_ARRAY_INDEX ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  frame_assign (struct stack*,int /*<<< orphan*/ ,struct value*) ; 
 int /*<<< orphan*/  free_number (struct number*) ; 
 int /*<<< orphan*/  get_ulong (struct number*) ; 
 struct value* pop () ; 
 struct number* pop_number () ; 
 int readreg () ; 
 int /*<<< orphan*/  stack_free_value (struct value*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
store_array(void)
{
	struct number *inumber;
	struct value *value;
	struct stack *stack;
	u_long idx;
	int reg;

	reg = readreg();
	if (reg >= 0) {
		inumber = pop_number();
		if (inumber == NULL)
			return;
		value = pop();
		if (value == NULL) {
			free_number(inumber);
			return;
		}
		idx = get_ulong(inumber);
		if (BN_is_negative(inumber->number)) {
			warnx("negative idx");
			stack_free_value(value);
		} else if (idx == ULONG_MAX || idx > MAX_ARRAY_INDEX) {
			warnx("idx too big");
			stack_free_value(value);
		} else {
			stack = &bmachine.reg[reg];
			frame_assign(stack, idx, value);
		}
		free_number(inumber);
	}
}