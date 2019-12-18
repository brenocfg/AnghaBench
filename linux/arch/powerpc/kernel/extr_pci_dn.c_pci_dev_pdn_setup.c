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
struct pci_dn {int dummy; } ;
struct TYPE_3__ {struct pci_dn* pci_data; } ;
struct TYPE_4__ {TYPE_1__ archdata; } ;
struct pci_dev {TYPE_2__ dev; } ;

/* Variables and functions */
 struct pci_dn* pci_get_pdn (struct pci_dev*) ; 

__attribute__((used)) static void pci_dev_pdn_setup(struct pci_dev *pdev)
{
	struct pci_dn *pdn;

	if (pdev->dev.archdata.pci_data)
		return;

	/* Setup the fast path */
	pdn = pci_get_pdn(pdev);
	pdev->dev.archdata.pci_data = pdn;
}