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
struct TYPE_2__ {char* string; struct number* num; } ;
struct value {int type; TYPE_1__ u; } ;
struct number {int /*<<< orphan*/  number; } ;

/* Variables and functions */
#define  BCODE_NONE 130 
#define  BCODE_NUMBER 129 
#define  BCODE_STRING 128 
 scalar_t__ BN_get_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_mask_bits (int /*<<< orphan*/ ,int) ; 
 int BN_num_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstrdup (char*) ; 
 int /*<<< orphan*/  normalize (struct number*,int /*<<< orphan*/ ) ; 
 struct value* pop () ; 
 int /*<<< orphan*/  push_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_free_value (struct value*) ; 

__attribute__((used)) static void
to_ascii(void)
{
	struct number *n;
	struct value *value;
	char str[2];

	value = pop();
	if (value != NULL) {
		str[1] = '\0';
		switch (value->type) {
		case BCODE_NONE:
			return;
		case BCODE_NUMBER:
			n = value->u.num;
			normalize(n, 0);
			if (BN_num_bits(n->number) > 8)
				bn_check(BN_mask_bits(n->number, 8));
			str[0] = (char)BN_get_word(n->number);
			break;
		case BCODE_STRING:
			str[0] = value->u.string[0];
			break;
		}
		stack_free_value(value);
		push_string(bstrdup(str));
	}
}