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
struct eeh_pe {int dummy; } ;
struct eeh_dev {struct eeh_pe* pe; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct eeh_pe*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EEH_RESET_HOT ; 
 TYPE_1__* eeh_ops ; 
 struct eeh_dev* pci_dev_to_eeh_dev (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct eeh_pe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pnv_npu_disable_device(struct pci_dev *pdev)
{
	struct eeh_dev *edev = pci_dev_to_eeh_dev(pdev);
	struct eeh_pe *eehpe = edev ? edev->pe : NULL;

	if (eehpe && eeh_ops && eeh_ops->reset)
		eeh_ops->reset(eehpe, EEH_RESET_HOT);
}