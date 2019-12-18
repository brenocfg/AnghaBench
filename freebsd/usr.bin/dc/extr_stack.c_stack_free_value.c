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
struct value {int type; int /*<<< orphan*/ * array; TYPE_1__ u; } ;

/* Variables and functions */
#define  BCODE_NONE 130 
#define  BCODE_NUMBER 129 
#define  BCODE_STRING 128 
 int /*<<< orphan*/  array_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_number (int /*<<< orphan*/ ) ; 

void
stack_free_value(struct value *v)
{

	switch (v->type) {
	case BCODE_NONE:
		break;
	case BCODE_NUMBER:
		free_number(v->u.num);
		break;
	case BCODE_STRING:
		free(v->u.string);
		break;
	}
	array_free(v->array);
	v->array = NULL;
}