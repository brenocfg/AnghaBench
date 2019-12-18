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
typedef  void* u32 ;
struct pci_bus {int dummy; } ;
struct TYPE_5__ {void* l; void** w; void** b; } ;
struct TYPE_4__ {TYPE_2__ config_data; int /*<<< orphan*/  config_addr; } ;
struct TYPE_6__ {TYPE_1__ pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int,int,void*) ; 
 int PCIBIOS_SUCCESSFUL ; 
 TYPE_3__* mace ; 
 int /*<<< orphan*/  mkaddr (struct pci_bus*,unsigned int,int) ; 

__attribute__((used)) static int
mace_pci_write_config(struct pci_bus *bus, unsigned int devfn,
		      int reg, int size, u32 val)
{
	mace->pci.config_addr = mkaddr(bus, devfn, reg);
	switch (size) {
	case 1:
		mace->pci.config_data.b[(reg & 3) ^ 3] = val;
		break;
	case 2:
		mace->pci.config_data.w[((reg >> 1) & 1) ^ 1] = val;
		break;
	case 4:
		mace->pci.config_data.l = val;
		break;
	}

	DPRINTK("write%d: reg=%08x,val=%02x\n", size * 8, reg, val);

	return PCIBIOS_SUCCESSFUL;
}