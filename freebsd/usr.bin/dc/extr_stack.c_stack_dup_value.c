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
struct TYPE_2__ {int /*<<< orphan*/ * string; int /*<<< orphan*/  num; } ;
struct value {int type; int /*<<< orphan*/ * array; TYPE_1__ u; } ;

/* Variables and functions */
#define  BCODE_NONE 130 
#define  BCODE_NUMBER 129 
#define  BCODE_STRING 128 
 int /*<<< orphan*/ * array_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dup_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ *) ; 

struct value *
stack_dup_value(const struct value *a, struct value *copy)
{

	copy->type = a->type;

	switch (a->type) {
	case BCODE_NONE:
		break;
	case BCODE_NUMBER:
		copy->u.num = dup_number(a->u.num);
		break;
	case BCODE_STRING:
		copy->u.string = strdup(a->u.string);
		if (copy->u.string == NULL)
			err(1, NULL);
		break;
	}

	copy->array = a->array == NULL ? NULL : array_dup(a->array);

	return (copy);
}