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
 int resource_int_value (char const*,int,char*,int*) ; 

int
resource_disabled(const char *name, int unit)
{
	int error, value;

	error = resource_int_value(name, unit, "disabled", &value);
	if (error)
	       return (0);
	return (value);
}