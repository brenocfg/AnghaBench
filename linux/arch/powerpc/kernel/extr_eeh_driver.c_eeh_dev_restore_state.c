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
struct pci_dev {int dummy; } ;
struct eeh_dev {TYPE_1__* pe; int /*<<< orphan*/  entry; } ;
struct TYPE_2__ {int state; int /*<<< orphan*/  edevs; } ;

/* Variables and functions */
 int EEH_PE_CFG_RESTRICTED ; 
 struct pci_dev* eeh_dev_to_pci_dev (struct eeh_dev*) ; 
 int /*<<< orphan*/  eeh_pe_restore_bars (TYPE_1__*) ; 
 scalar_t__ list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 

__attribute__((used)) static void eeh_dev_restore_state(struct eeh_dev *edev, void *userdata)
{
	struct pci_dev *pdev;

	if (!edev)
		return;

	/*
	 * The content in the config space isn't saved because
	 * the blocked config space on some adapters. We have
	 * to restore the initial saved config space when the
	 * EEH device is created.
	 */
	if (edev->pe && (edev->pe->state & EEH_PE_CFG_RESTRICTED)) {
		if (list_is_last(&edev->entry, &edev->pe->edevs))
			eeh_pe_restore_bars(edev->pe);

		return;
	}

	pdev = eeh_dev_to_pci_dev(edev);
	if (!pdev)
		return;

	pci_restore_state(pdev);
}