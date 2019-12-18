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
struct si_sm_io {unsigned long addr_data; int regsize; int io_size; int regspacing; int /*<<< orphan*/  io_cleanup; int /*<<< orphan*/ * addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  outputb; int /*<<< orphan*/  inputb; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  SI_DEVICE_NAME ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  intf_mem_inb ; 
 int /*<<< orphan*/  intf_mem_inl ; 
 int /*<<< orphan*/  intf_mem_inw ; 
 int /*<<< orphan*/  intf_mem_outb ; 
 int /*<<< orphan*/  intf_mem_outl ; 
 int /*<<< orphan*/  intf_mem_outw ; 
 int /*<<< orphan*/ * ioremap (unsigned long,int) ; 
 int /*<<< orphan*/  mem_cleanup ; 
 int /*<<< orphan*/  mem_inq ; 
 int /*<<< orphan*/  mem_outq ; 
 int /*<<< orphan*/  mem_region_cleanup (struct si_sm_io*,int) ; 
 int /*<<< orphan*/ * request_mem_region (unsigned long,int,int /*<<< orphan*/ ) ; 

int ipmi_si_mem_setup(struct si_sm_io *io)
{
	unsigned long addr = io->addr_data;
	int           mapsize, idx;

	if (!addr)
		return -ENODEV;

	/*
	 * Figure out the actual readb/readw/readl/etc routine to use based
	 * upon the register size.
	 */
	switch (io->regsize) {
	case 1:
		io->inputb = intf_mem_inb;
		io->outputb = intf_mem_outb;
		break;
	case 2:
		io->inputb = intf_mem_inw;
		io->outputb = intf_mem_outw;
		break;
	case 4:
		io->inputb = intf_mem_inl;
		io->outputb = intf_mem_outl;
		break;
#ifdef readq
	case 8:
		io->inputb = mem_inq;
		io->outputb = mem_outq;
		break;
#endif
	default:
		dev_warn(io->dev, "Invalid register size: %d\n",
			 io->regsize);
		return -EINVAL;
	}

	/*
	 * Some BIOSes reserve disjoint memory regions in their ACPI
	 * tables.  This causes problems when trying to request the
	 * entire region.  Therefore we must request each register
	 * separately.
	 */
	for (idx = 0; idx < io->io_size; idx++) {
		if (request_mem_region(addr + idx * io->regspacing,
				       io->regsize, SI_DEVICE_NAME) == NULL) {
			/* Undo allocations */
			mem_region_cleanup(io, idx);
			return -EIO;
		}
	}

	/*
	 * Calculate the total amount of memory to claim.  This is an
	 * unusual looking calculation, but it avoids claiming any
	 * more memory than it has to.  It will claim everything
	 * between the first address to the end of the last full
	 * register.
	 */
	mapsize = ((io->io_size * io->regspacing)
		   - (io->regspacing - io->regsize));
	io->addr = ioremap(addr, mapsize);
	if (io->addr == NULL) {
		mem_region_cleanup(io, io->io_size);
		return -EIO;
	}

	io->io_cleanup = mem_cleanup;

	return 0;
}