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
typedef  int u32 ;

/* Variables and functions */
 int PCI_P2P_BUS_MASK ; 
 int PCI_P2P_BUS_OFFS ; 
 int /*<<< orphan*/  PCI_P2P_CONF ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int orion5x_pci_local_bus_nr(void)
{
	u32 conf = readl(PCI_P2P_CONF);
	return((conf & PCI_P2P_BUS_MASK) >> PCI_P2P_BUS_OFFS);
}