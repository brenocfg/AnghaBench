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
struct bcma_bus {scalar_t__ hosttype; int /*<<< orphan*/  host_pci; } ;

/* Variables and functions */
 scalar_t__ BCMA_HOSTTYPE_PCI ; 
 int /*<<< orphan*/  BCMA_PCI_BAR0_WIN ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcma_scan_switch_core(struct bcma_bus *bus, u32 addr)
{
	if (bus->hosttype == BCMA_HOSTTYPE_PCI)
		pci_write_config_dword(bus->host_pci, BCMA_PCI_BAR0_WIN,
				       addr);
}