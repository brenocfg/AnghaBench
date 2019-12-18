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
typedef  int pcell_t ;
typedef  int /*<<< orphan*/ * bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int BUS_SPACE_MAP_PREFETCHABLE ; 
 int OFW_PADDR_NOT_PCI ; 
 int OFW_PCI_PHYS_HI_PREFETCHABLE ; 
 int /*<<< orphan*/  bs_be_tag ; 
 int /*<<< orphan*/  bs_le_tag ; 
 int bus_space_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int ofw_reg_to_paddr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

int
OF_decode_addr(phandle_t dev, int regno, bus_space_tag_t *tag,
    bus_space_handle_t *handle, bus_size_t *sz)
{
	bus_addr_t addr;
	bus_size_t size;
	pcell_t pci_hi;
	int flags, res;

	res = ofw_reg_to_paddr(dev, regno, &addr, &size, &pci_hi);
	if (res < 0)
		return (res);

	if (pci_hi == OFW_PADDR_NOT_PCI) {
		*tag = &bs_be_tag;
		flags = 0;
	} else {
		*tag = &bs_le_tag;
		flags = (pci_hi & OFW_PCI_PHYS_HI_PREFETCHABLE) ? 
		    BUS_SPACE_MAP_PREFETCHABLE: 0;
	}

	if (sz != NULL)
		*sz = size;

	return (bus_space_map(*tag, addr, size, flags, handle));
}