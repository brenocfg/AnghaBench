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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ bus_space_handle_t ;

/* Variables and functions */
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 

void *
paddr_map(uint32_t offset, uint32_t phys, uint32_t size)
{
	bus_space_handle_t bsh;

	if (bus_space_map(fdtbus_bs_tag, (phys + offset),
			size, 0, &bsh) != 0) {
		panic("Couldn't map 0x%08x\n", (phys + offset));
	}

	return (void *)(bsh);
}