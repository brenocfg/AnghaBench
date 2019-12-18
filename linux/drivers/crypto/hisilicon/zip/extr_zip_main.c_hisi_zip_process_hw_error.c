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
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct hisi_zip {int /*<<< orphan*/  qm; } ;
typedef  scalar_t__ pci_ers_result_t ;

/* Variables and functions */
 scalar_t__ PCI_ERS_RESULT_NEED_RESET ; 
 scalar_t__ PCI_ERS_RESULT_NONE ; 
 scalar_t__ PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ hisi_qm_hw_error_handle (int /*<<< orphan*/ *) ; 
 scalar_t__ hisi_zip_hw_error_handle (struct hisi_zip*) ; 
 struct hisi_zip* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t hisi_zip_process_hw_error(struct pci_dev *pdev)
{
	struct hisi_zip *hisi_zip = pci_get_drvdata(pdev);
	struct device *dev = &pdev->dev;
	pci_ers_result_t qm_ret, zip_ret;

	if (!hisi_zip) {
		dev_err(dev,
			"Can't recover ZIP-error occurred during device init\n");
		return PCI_ERS_RESULT_NONE;
	}

	qm_ret = hisi_qm_hw_error_handle(&hisi_zip->qm);

	zip_ret = hisi_zip_hw_error_handle(hisi_zip);

	return (qm_ret == PCI_ERS_RESULT_NEED_RESET ||
		zip_ret == PCI_ERS_RESULT_NEED_RESET) ?
	       PCI_ERS_RESULT_NEED_RESET : PCI_ERS_RESULT_RECOVERED;
}