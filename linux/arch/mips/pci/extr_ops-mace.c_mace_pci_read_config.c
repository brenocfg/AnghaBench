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
typedef  int u32 ;
struct pci_bus {scalar_t__ number; } ;
struct TYPE_4__ {int* b; int* w; int l; } ;
struct TYPE_5__ {int control; int /*<<< orphan*/  error; TYPE_1__ config_data; int /*<<< orphan*/  config_addr; } ;
struct TYPE_6__ {TYPE_2__ pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int,int,int) ; 
 int MACEPCI_CONTROL_MAR_INT ; 
 int /*<<< orphan*/  MACEPCI_ERROR_MASTER_ABORT ; 
 int PCIBIOS_SUCCESSFUL ; 
 TYPE_3__* mace ; 
 int /*<<< orphan*/  mkaddr (struct pci_bus*,unsigned int,int) ; 

__attribute__((used)) static int
mace_pci_read_config(struct pci_bus *bus, unsigned int devfn,
		     int reg, int size, u32 *val)
{
	u32 control = mace->pci.control;

	/* disable master aborts interrupts during config read */
	mace->pci.control = control & ~MACEPCI_CONTROL_MAR_INT;
	mace->pci.config_addr = mkaddr(bus, devfn, reg);
	switch (size) {
	case 1:
		*val = mace->pci.config_data.b[(reg & 3) ^ 3];
		break;
	case 2:
		*val = mace->pci.config_data.w[((reg >> 1) & 1) ^ 1];
		break;
	case 4:
		*val = mace->pci.config_data.l;
		break;
	}
	/* ack possible master abort */
	mace->pci.error &= ~MACEPCI_ERROR_MASTER_ABORT;
	mace->pci.control = control;
	/*
	 * someone forgot to set the ultra bit for the onboard
	 * scsi chips; we fake it here
	 */
	if (bus->number == 0 && reg == 0x40 && size == 4 &&
	    (devfn == (1 << 3) || devfn == (2 << 3)))
		*val |= 0x1000;

	DPRINTK("read%d: reg=%08x,val=%02x\n", size * 8, reg, *val);

	return PCIBIOS_SUCCESSFUL;
}