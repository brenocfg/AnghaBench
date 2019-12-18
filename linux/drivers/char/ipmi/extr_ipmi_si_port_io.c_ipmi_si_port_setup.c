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
struct si_sm_io {unsigned int addr_data; int io_size; int regspacing; int /*<<< orphan*/  io_cleanup; int /*<<< orphan*/  regsize; int /*<<< orphan*/  dev; int /*<<< orphan*/  outputb; int /*<<< orphan*/  inputb; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  SI_DEVICE_NAME ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_cleanup ; 
 int /*<<< orphan*/  port_inb ; 
 int /*<<< orphan*/  port_inl ; 
 int /*<<< orphan*/  port_inw ; 
 int /*<<< orphan*/  port_outb ; 
 int /*<<< orphan*/  port_outl ; 
 int /*<<< orphan*/  port_outw ; 
 int /*<<< orphan*/  release_region (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * request_region (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ipmi_si_port_setup(struct si_sm_io *io)
{
	unsigned int addr = io->addr_data;
	int          idx;

	if (!addr)
		return -ENODEV;

	/*
	 * Figure out the actual inb/inw/inl/etc routine to use based
	 * upon the register size.
	 */
	switch (io->regsize) {
	case 1:
		io->inputb = port_inb;
		io->outputb = port_outb;
		break;
	case 2:
		io->inputb = port_inw;
		io->outputb = port_outw;
		break;
	case 4:
		io->inputb = port_inl;
		io->outputb = port_outl;
		break;
	default:
		dev_warn(io->dev, "Invalid register size: %d\n",
			 io->regsize);
		return -EINVAL;
	}

	/*
	 * Some BIOSes reserve disjoint I/O regions in their ACPI
	 * tables.  This causes problems when trying to register the
	 * entire I/O region.  Therefore we must register each I/O
	 * port separately.
	 */
	for (idx = 0; idx < io->io_size; idx++) {
		if (request_region(addr + idx * io->regspacing,
				   io->regsize, SI_DEVICE_NAME) == NULL) {
			/* Undo allocations */
			while (idx--)
				release_region(addr + idx * io->regspacing,
					       io->regsize);
			return -EIO;
		}
	}

	io->io_cleanup = port_cleanup;

	return 0;
}