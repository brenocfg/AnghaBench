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
struct acpi_device_id {char* member_0; int /*<<< orphan*/  member_1; } ;
struct acpi_device {struct acpi_device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_match_device_ids (struct acpi_device*,struct acpi_device_id const*) ; 

__attribute__((used)) static bool acpi_is_indirect_io_slave(struct acpi_device *device)
{
	struct acpi_device *parent = device->parent;
	static const struct acpi_device_id indirect_io_hosts[] = {
		{"HISI0191", 0},
		{}
	};

	return parent && !acpi_match_device_ids(parent, indirect_io_hosts);
}