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
 scalar_t__ ENFORCE_RESOURCES_STRICT ; 
 scalar_t__ acpi_enforce_resources ; 

int acpi_resources_are_enforced(void)
{
	return acpi_enforce_resources == ENFORCE_RESOURCES_STRICT;
}