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
typedef  int /*<<< orphan*/  u32 ;
struct pci_bus {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIMT_CONFIG_DATA ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inw (int /*<<< orphan*/ ) ; 
 int set_config_address (int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int pcimt_read(struct pci_bus *bus, unsigned int devfn, int reg,
		      int size, u32 * val)
{
	int res;

	if ((res = set_config_address(bus->number, devfn, reg)))
		return res;

	switch (size) {
	case 1:
		*val = inb(PCIMT_CONFIG_DATA + (reg & 3));
		break;
	case 2:
		*val = inw(PCIMT_CONFIG_DATA + (reg & 2));
		break;
	case 4:
		*val = inl(PCIMT_CONFIG_DATA);
		break;
	}

	return 0;
}