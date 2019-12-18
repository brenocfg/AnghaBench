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
typedef  int /*<<< orphan*/  heim_object_t ;
typedef  TYPE_1__* heim_array_t ;
struct TYPE_3__ {int len; int /*<<< orphan*/ * val; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  heim_retain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

int
heim_array_append_value(heim_array_t array, heim_object_t object)
{
    heim_object_t *ptr;

    ptr = realloc(array->val, (array->len + 1) * sizeof(array->val[0]));
    if (ptr == NULL)
	return ENOMEM;
    array->val = ptr;
    array->val[array->len++] = heim_retain(object);

    return 0;
}