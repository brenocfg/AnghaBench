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
struct pci_dev {scalar_t__ revision; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  enum pci_channel_state { ____Placeholder_pci_channel_state } pci_channel_state ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NONE ; 
 scalar_t__ RSXX_EEH_SUPPORT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  rsxx_eeh_failure (struct pci_dev*) ; 
 int rsxx_eeh_frozen (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t rsxx_error_detected(struct pci_dev *dev,
					    enum pci_channel_state error)
{
	int st;

	if (dev->revision < RSXX_EEH_SUPPORT)
		return PCI_ERS_RESULT_NONE;

	if (error == pci_channel_io_perm_failure) {
		rsxx_eeh_failure(dev);
		return PCI_ERS_RESULT_DISCONNECT;
	}

	st = rsxx_eeh_frozen(dev);
	if (st) {
		dev_err(&dev->dev, "Slot reset setup failed\n");
		rsxx_eeh_failure(dev);
		return PCI_ERS_RESULT_DISCONNECT;
	}

	return PCI_ERS_RESULT_NEED_RESET;
}