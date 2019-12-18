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
typedef  int /*<<< orphan*/  heim_bool_t ;

/* Variables and functions */
 int heim_base_tagged_object_value (int /*<<< orphan*/ ) ; 

int
heim_bool_val(heim_bool_t ptr)
{
    return heim_base_tagged_object_value(ptr);
}