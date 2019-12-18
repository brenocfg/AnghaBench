#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int flags; } ;
struct acpi_resource_memory32 {int minimum; int address_length; int /*<<< orphan*/  write_protect; } ;
struct acpi_resource_memory24 {int minimum; int address_length; int /*<<< orphan*/  write_protect; } ;
struct acpi_resource_fixed_memory32 {int address; int address_length; int /*<<< orphan*/  write_protect; } ;
struct TYPE_2__ {struct acpi_resource_fixed_memory32 fixed_memory32; struct acpi_resource_memory32 memory32; struct acpi_resource_memory24 memory24; } ;
struct acpi_resource {int type; TYPE_1__ data; } ;

/* Variables and functions */
#define  ACPI_RESOURCE_TYPE_FIXED_MEMORY32 130 
#define  ACPI_RESOURCE_TYPE_MEMORY24 129 
#define  ACPI_RESOURCE_TYPE_MEMORY32 128 
 int IORESOURCE_DISABLED ; 
 int /*<<< orphan*/  acpi_dev_get_memresource (struct resource*,int,int,int /*<<< orphan*/ ) ; 

bool acpi_dev_resource_memory(struct acpi_resource *ares, struct resource *res)
{
	struct acpi_resource_memory24 *memory24;
	struct acpi_resource_memory32 *memory32;
	struct acpi_resource_fixed_memory32 *fixed_memory32;

	switch (ares->type) {
	case ACPI_RESOURCE_TYPE_MEMORY24:
		memory24 = &ares->data.memory24;
		acpi_dev_get_memresource(res, memory24->minimum << 8,
					 memory24->address_length << 8,
					 memory24->write_protect);
		break;
	case ACPI_RESOURCE_TYPE_MEMORY32:
		memory32 = &ares->data.memory32;
		acpi_dev_get_memresource(res, memory32->minimum,
					 memory32->address_length,
					 memory32->write_protect);
		break;
	case ACPI_RESOURCE_TYPE_FIXED_MEMORY32:
		fixed_memory32 = &ares->data.fixed_memory32;
		acpi_dev_get_memresource(res, fixed_memory32->address,
					 fixed_memory32->address_length,
					 fixed_memory32->write_protect);
		break;
	default:
		res->flags = 0;
		return false;
	}

	return !(res->flags & IORESOURCE_DISABLED);
}