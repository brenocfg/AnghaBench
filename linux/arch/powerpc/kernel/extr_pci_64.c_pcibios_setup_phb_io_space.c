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
struct pci_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcibios_map_phb_io_space (struct pci_controller*) ; 

void pcibios_setup_phb_io_space(struct pci_controller *hose)
{
	pcibios_map_phb_io_space(hose);
}