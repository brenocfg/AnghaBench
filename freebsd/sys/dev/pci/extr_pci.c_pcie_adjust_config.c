#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int pcie_location; } ;
struct TYPE_4__ {TYPE_1__ pcie; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

uint32_t
pcie_adjust_config(device_t dev, int reg, uint32_t mask, uint32_t value,
    int width)
{
	struct pci_devinfo *dinfo = device_get_ivars(dev);
	uint32_t old, new;
	int cap;

	cap = dinfo->cfg.pcie.pcie_location;
	if (cap == 0) {
		if (width == 2)
			return (0xffff);
		return (0xffffffff);
	}

	old = pci_read_config(dev, cap + reg, width);
	new = old & ~mask;
	new |= (value & mask);
	pci_write_config(dev, cap + reg, new, width);
	return (old);
}