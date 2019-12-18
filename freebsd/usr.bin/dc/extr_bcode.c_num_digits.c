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
struct TYPE_2__ {int /*<<< orphan*/  string; int /*<<< orphan*/  num; } ;
struct value {int type; TYPE_1__ u; } ;
struct number {int /*<<< orphan*/  number; } ;

/* Variables and functions */
#define  BCODE_NONE 130 
#define  BCODE_NUMBER 129 
#define  BCODE_STRING 128 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 size_t count_digits (int /*<<< orphan*/ ) ; 
 struct number* new_number () ; 
 struct value* pop () ; 
 int /*<<< orphan*/  push_number (struct number*) ; 
 int /*<<< orphan*/  stack_free_value (struct value*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
num_digits(void)
{
	struct number *n = NULL;
	struct value *value;
	size_t digits;

	value = pop();
	if (value != NULL) {
		switch (value->type) {
		case BCODE_NONE:
			return;
		case BCODE_NUMBER:
			digits = count_digits(value->u.num);
			n = new_number();
			bn_check(BN_set_word(n->number, digits));
			break;
		case BCODE_STRING:
			digits = strlen(value->u.string);
			n = new_number();
			bn_check(BN_set_word(n->number, digits));
			break;
		}
		stack_free_value(value);
		push_number(n);
	}
}