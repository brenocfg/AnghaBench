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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/ * bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int bus_space_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmap_bus ; 
 int ofw_reg_to_paddr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
OF_decode_addr(phandle_t dev, int regno, bus_space_tag_t *tag,
    bus_space_handle_t *handle, bus_size_t *sz)
{
	bus_addr_t addr;
	bus_size_t size;
	int err;

	err = ofw_reg_to_paddr(dev, regno, &addr, &size, NULL);
	if (err != 0)
		return (err);

	*tag = &memmap_bus;

	if (sz != NULL)
		*sz = size;

	return (bus_space_map(*tag, addr, size, 0, handle));
}