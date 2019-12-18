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
struct TYPE_3__ {size_t len; int /*<<< orphan*/ * val; } ;

/* Variables and functions */
 int /*<<< orphan*/  heim_abort (char*) ; 
 int /*<<< orphan*/  heim_retain (int /*<<< orphan*/ ) ; 

heim_object_t
heim_array_copy_value(heim_array_t array, size_t idx)
{
    if (idx >= array->len)
	heim_abort("index too large");
    return heim_retain(array->val[idx]);
}