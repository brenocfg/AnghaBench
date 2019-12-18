#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_4__ {TYPE_1__* num; } ;
struct value {int type; TYPE_2__ u; } ;
struct number {int /*<<< orphan*/  number; } ;
struct TYPE_3__ {int /*<<< orphan*/  scale; } ;

/* Variables and functions */
#define  BCODE_NONE 130 
#define  BCODE_NUMBER 129 
#define  BCODE_STRING 128 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 struct number* new_number () ; 
 struct value* pop () ; 
 int /*<<< orphan*/  push_number (struct number*) ; 
 int /*<<< orphan*/  stack_free_value (struct value*) ; 

__attribute__((used)) static void
push_scale(void)
{
	struct number *n;
	struct value *value;
	u_int scale = 0;

	value = pop();
	if (value != NULL) {
		switch (value->type) {
		case BCODE_NONE:
			return;
		case BCODE_NUMBER:
			scale = value->u.num->scale;
			break;
		case BCODE_STRING:
			break;
		}
		stack_free_value(value);
		n = new_number();
		bn_check(BN_set_word(n->number, scale));
		push_number(n);
	}
}