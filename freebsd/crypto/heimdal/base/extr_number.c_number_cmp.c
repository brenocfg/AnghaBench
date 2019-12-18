#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ heim_base_is_tagged_object (void*) ; 
 int heim_base_tagged_object_value (void*) ; 

__attribute__((used)) static int
number_cmp(void *a, void *b)
{
    int na, nb;

    if (heim_base_is_tagged_object(a))
	na = heim_base_tagged_object_value(a);
    else
	na = *(int *)a;

    if (heim_base_is_tagged_object(b))
	nb = heim_base_tagged_object_value(b);
    else
	nb = *(int *)b;

    return na - nb;
}