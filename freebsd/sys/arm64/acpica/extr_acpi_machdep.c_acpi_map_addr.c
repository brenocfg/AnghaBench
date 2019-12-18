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
struct acpi_generic_address {scalar_t__ SpaceId; int /*<<< orphan*/  Address; } ;
typedef  int /*<<< orphan*/ * bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int ENXIO ; 
 int bus_space_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmap_bus ; 

int
acpi_map_addr(struct acpi_generic_address *addr, bus_space_tag_t *tag,
    bus_space_handle_t *handle, bus_size_t size)
{
	bus_addr_t phys;

	/* Check if the device is Memory mapped */
	if (addr->SpaceId != 0)
		return (ENXIO);

	phys = addr->Address;
	*tag = &memmap_bus;

	return (bus_space_map(*tag, phys, size, 0, handle));
}