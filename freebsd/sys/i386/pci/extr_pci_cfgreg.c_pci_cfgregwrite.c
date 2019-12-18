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
typedef  int /*<<< orphan*/  u_int32_t ;

/* Variables and functions */
 scalar_t__ CFGMECH_PCIE ; 
 scalar_t__ cfgmech ; 
 int pcie_badslots ; 
 int pcie_maxbus ; 
 int pcie_minbus ; 
 int /*<<< orphan*/  pciereg_cfgwrite (int,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcireg_cfgwrite (int,int,int,int,int /*<<< orphan*/ ,int) ; 

void
pci_cfgregwrite(int bus, int slot, int func, int reg, u_int32_t data, int bytes)
{

	if (cfgmech == CFGMECH_PCIE &&
	    (bus >= pcie_minbus && bus <= pcie_maxbus) &&
	    (bus != 0 || !(1 << slot & pcie_badslots)))
		pciereg_cfgwrite(bus, slot, func, reg, data, bytes);
	else
		pcireg_cfgwrite(bus, slot, func, reg, data, bytes);
}