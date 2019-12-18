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
struct pci_dev {int dummy; } ;
struct adf_accel_dev {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADF_DEV_RESET_SYNC ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 scalar_t__ adf_dev_aer_schedule_reset (struct adf_accel_dev*,int /*<<< orphan*/ ) ; 
 struct adf_accel_dev* adf_devmgr_pci_to_accel_dev (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static pci_ers_result_t adf_slot_reset(struct pci_dev *pdev)
{
	struct adf_accel_dev *accel_dev = adf_devmgr_pci_to_accel_dev(pdev);

	if (!accel_dev) {
		pr_err("QAT: Can't find acceleration device\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}
	if (adf_dev_aer_schedule_reset(accel_dev, ADF_DEV_RESET_SYNC))
		return PCI_ERS_RESULT_DISCONNECT;

	return PCI_ERS_RESULT_RECOVERED;
}