#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* elements; } ;
union acpi_object {TYPE_3__ package; } ;
typedef  scalar_t__ acpi_handle ;
struct TYPE_4__ {scalar_t__ handle; } ;
struct TYPE_5__ {TYPE_1__ reference; } ;

/* Variables and functions */

__attribute__((used)) static bool acpi_power_resource_is_dup(union acpi_object *package,
				       unsigned int start, unsigned int i)
{
	acpi_handle rhandle, dup;
	unsigned int j;

	/* The caller is expected to check the package element types */
	rhandle = package->package.elements[i].reference.handle;
	for (j = start; j < i; j++) {
		dup = package->package.elements[j].reference.handle;
		if (dup == rhandle)
			return true;
	}

	return false;
}