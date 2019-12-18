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
typedef  scalar_t__ heim_number_t ;

/* Variables and functions */
 scalar_t__ heim_base_is_tagged_object (scalar_t__) ; 
 int heim_base_tagged_object_value (scalar_t__) ; 

int
heim_number_get_int(heim_number_t number)
{
    if (heim_base_is_tagged_object(number))
	return heim_base_tagged_object_value(number);
    return *(int *)number;
}