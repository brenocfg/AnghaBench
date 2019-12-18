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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hisi_zip {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hisi_zip_clear_vft_config (struct hisi_zip*) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 struct hisi_zip* pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ pci_vfs_assigned (struct pci_dev*) ; 

__attribute__((used)) static int hisi_zip_sriov_disable(struct pci_dev *pdev)
{
	struct hisi_zip *hisi_zip = pci_get_drvdata(pdev);

	if (pci_vfs_assigned(pdev)) {
		dev_err(&pdev->dev,
			"Can't disable VFs while VFs are assigned!\n");
		return -EPERM;
	}

	/* remove in hisi_zip_pci_driver will be called to free VF resources */
	pci_disable_sriov(pdev);

	return hisi_zip_clear_vft_config(hisi_zip);
}