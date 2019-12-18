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
struct pci_driver {TYPE_1__* err_handler; int /*<<< orphan*/  name; } ;
struct pci_dev {int dummy; } ;
struct eeh_dev {int /*<<< orphan*/  in_error; } ;
typedef  enum pci_ers_result { ____Placeholder_pci_ers_result } pci_ers_result ;
struct TYPE_2__ {int (* slot_reset ) (struct pci_dev*) ;} ;

/* Variables and functions */
 int PCI_ERS_RESULT_NONE ; 
 int /*<<< orphan*/  eeh_edev_info (struct eeh_dev*,char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct pci_dev*) ; 

__attribute__((used)) static enum pci_ers_result eeh_report_reset(struct eeh_dev *edev,
					    struct pci_dev *pdev,
					    struct pci_driver *driver)
{
	if (!driver->err_handler->slot_reset || !edev->in_error)
		return PCI_ERS_RESULT_NONE;
	eeh_edev_info(edev, "Invoking %s->slot_reset()", driver->name);
	return driver->err_handler->slot_reset(pdev);
}