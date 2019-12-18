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
struct bcma_drv_pci {int early_setup_done; scalar_t__ hostmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_core_pci_fixcfg (struct bcma_drv_pci*) ; 
 scalar_t__ bcma_core_pci_is_in_hostmode (struct bcma_drv_pci*) ; 

void bcma_core_pci_early_init(struct bcma_drv_pci *pc)
{
	if (pc->early_setup_done)
		return;

	pc->hostmode = bcma_core_pci_is_in_hostmode(pc);
	if (pc->hostmode)
		goto out;

	bcma_core_pci_fixcfg(pc);

out:
	pc->early_setup_done = true;
}