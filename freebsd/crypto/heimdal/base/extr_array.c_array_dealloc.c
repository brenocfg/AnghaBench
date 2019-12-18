#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* heim_object_t ;
typedef  TYPE_1__* heim_array_t ;
struct TYPE_4__ {size_t len; int /*<<< orphan*/ * val; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heim_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
array_dealloc(heim_object_t ptr)
{
    heim_array_t array = ptr;
    size_t n;
    for (n = 0; n < array->len; n++)
	heim_release(array->val[n]);
    free(array->val);
}