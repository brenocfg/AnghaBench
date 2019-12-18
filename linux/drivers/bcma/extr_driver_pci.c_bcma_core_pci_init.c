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
struct bcma_drv_pci {scalar_t__ hostmode; scalar_t__ setup_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_core_pci_clientmode_init (struct bcma_drv_pci*) ; 
 int /*<<< orphan*/  bcma_core_pci_early_init (struct bcma_drv_pci*) ; 
 int /*<<< orphan*/  bcma_core_pci_hostmode_init (struct bcma_drv_pci*) ; 

void bcma_core_pci_init(struct bcma_drv_pci *pc)
{
	if (pc->setup_done)
		return;

	bcma_core_pci_early_init(pc);

	if (pc->hostmode)
		bcma_core_pci_hostmode_init(pc);
	else
		bcma_core_pci_clientmode_init(pc);
}