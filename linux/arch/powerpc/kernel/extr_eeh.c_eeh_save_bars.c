#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dn {int dummy; } ;
struct eeh_dev {int mode; int /*<<< orphan*/ * config_space; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_config ) (struct pci_dn*,int,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EEH_DEV_BRIDGE ; 
 int /*<<< orphan*/  PCI_COMMAND_MASTER ; 
 struct pci_dn* eeh_dev_to_pdn (struct eeh_dev*) ; 
 TYPE_1__* eeh_ops ; 
 int /*<<< orphan*/  stub1 (struct pci_dn*,int,int,int /*<<< orphan*/ *) ; 

void eeh_save_bars(struct eeh_dev *edev)
{
	struct pci_dn *pdn;
	int i;

	pdn = eeh_dev_to_pdn(edev);
	if (!pdn)
		return;

	for (i = 0; i < 16; i++)
		eeh_ops->read_config(pdn, i * 4, 4, &edev->config_space[i]);

	/*
	 * For PCI bridges including root port, we need enable bus
	 * master explicitly. Otherwise, it can't fetch IODA table
	 * entries correctly. So we cache the bit in advance so that
	 * we can restore it after reset, either PHB range or PE range.
	 */
	if (edev->mode & EEH_DEV_BRIDGE)
		edev->config_space[1] |= PCI_COMMAND_MASTER;
}