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
struct ntb_softc {int /*<<< orphan*/  device; struct ntb_pci_bar_info* bar_info; } ;
struct ntb_pci_bar_info {int /*<<< orphan*/ * pci_resource; int /*<<< orphan*/  pci_resource_id; } ;

/* Variables and functions */
 int NTB_MAX_BARS ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
intel_ntb_unmap_pci_bar(struct ntb_softc *ntb)
{
	struct ntb_pci_bar_info *current_bar;
	int i;

	for (i = 0; i < NTB_MAX_BARS; i++) {
		current_bar = &ntb->bar_info[i];
		if (current_bar->pci_resource != NULL)
			bus_release_resource(ntb->device, SYS_RES_MEMORY,
			    current_bar->pci_resource_id,
			    current_bar->pci_resource);
	}
}