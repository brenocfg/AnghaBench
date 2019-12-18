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
typedef  int u32 ;
struct pci_bus {unsigned int number; } ;
struct TYPE_2__ {int (* write ) (unsigned int,unsigned int,unsigned int,int,int,unsigned long) ;int /*<<< orphan*/  (* read ) (unsigned int,unsigned int,unsigned int,int,int,int*) ;} ;

/* Variables and functions */
 int PCI_BASE_ADDRESS_0 ; 
 unsigned int pci_domain_nr (struct pci_bus*) ; 
 TYPE_1__* raw_pci_ext_ops ; 
 int /*<<< orphan*/  stub1 (unsigned int,unsigned int,unsigned int,int,int,int*) ; 
 int stub2 (unsigned int,unsigned int,unsigned int,int,int,unsigned long) ; 
 int stub3 (unsigned int,unsigned int,unsigned int,int,int,int) ; 

__attribute__((used)) static int pci_device_update_fixed(struct pci_bus *bus, unsigned int devfn,
				   int reg, int len, u32 val, int offset)
{
	u32 size;
	unsigned int domain, busnum;
	int bar = (reg - PCI_BASE_ADDRESS_0) >> 2;

	domain = pci_domain_nr(bus);
	busnum = bus->number;

	if (val == ~0 && len == 4) {
		unsigned long decode;

		raw_pci_ext_ops->read(domain, busnum, devfn,
			       offset + 8 + (bar * 4), 4, &size);

		/* Turn the size into a decode pattern for the sizing code */
		if (size) {
			decode = size - 1;
			decode |= decode >> 1;
			decode |= decode >> 2;
			decode |= decode >> 4;
			decode |= decode >> 8;
			decode |= decode >> 16;
			decode++;
			decode = ~(decode - 1);
		} else {
			decode = 0;
		}

		/*
		 * If val is all ones, the core code is trying to size the reg,
		 * so update the mmconfig space with the real size.
		 *
		 * Note: this assumes the fixed size we got is a power of two.
		 */
		return raw_pci_ext_ops->write(domain, busnum, devfn, reg, 4,
				       decode);
	}

	/* This is some other kind of BAR write, so just do it. */
	return raw_pci_ext_ops->write(domain, busnum, devfn, reg, len, val);
}