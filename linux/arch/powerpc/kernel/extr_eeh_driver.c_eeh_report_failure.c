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
struct eeh_dev {int dummy; } ;
typedef  enum pci_ers_result { ____Placeholder_pci_ers_result } pci_ers_result ;
struct TYPE_2__ {int (* error_detected ) (struct pci_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int PCI_ERS_RESULT_NONE ; 
 int /*<<< orphan*/  eeh_edev_info (struct eeh_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_uevent_ers (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int stub1 (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum pci_ers_result eeh_report_failure(struct eeh_dev *edev,
					      struct pci_dev *pdev,
					      struct pci_driver *driver)
{
	enum pci_ers_result rc;

	if (!driver->err_handler->error_detected)
		return PCI_ERS_RESULT_NONE;

	eeh_edev_info(edev, "Invoking %s->error_detected(permanent failure)",
		      driver->name);
	rc = driver->err_handler->error_detected(pdev,
						 pci_channel_io_perm_failure);

	pci_uevent_ers(pdev, PCI_ERS_RESULT_DISCONNECT);
	return rc;
}