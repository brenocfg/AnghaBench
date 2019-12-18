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
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cpt_device {int num_vf_en; int /*<<< orphan*/  flags; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPT_FLAG_SRIOV_ENABLED ; 
 int ENODEV ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_SRIOV ; 
 scalar_t__ PCI_SRIOV_TOTAL_VF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int pci_enable_sriov (struct pci_dev*,int) ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 

__attribute__((used)) static int cpt_sriov_init(struct cpt_device *cpt, int num_vfs)
{
	int pos = 0;
	int err;
	u16 total_vf_cnt;
	struct pci_dev *pdev = cpt->pdev;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_SRIOV);
	if (!pos) {
		dev_err(&pdev->dev, "SRIOV capability is not found in PCIe config space\n");
		return -ENODEV;
	}

	cpt->num_vf_en = num_vfs; /* User requested VFs */
	pci_read_config_word(pdev, (pos + PCI_SRIOV_TOTAL_VF), &total_vf_cnt);
	if (total_vf_cnt < cpt->num_vf_en)
		cpt->num_vf_en = total_vf_cnt;

	if (!total_vf_cnt)
		return 0;

	/*Enabled the available VFs */
	err = pci_enable_sriov(pdev, cpt->num_vf_en);
	if (err) {
		dev_err(&pdev->dev, "SRIOV enable failed, num VF is %d\n",
			cpt->num_vf_en);
		cpt->num_vf_en = 0;
		return err;
	}

	/* TODO: Optionally enable static VQ priorities feature */

	dev_info(&pdev->dev, "SRIOV enabled, number of VF available %d\n",
		 cpt->num_vf_en);

	cpt->flags |= CPT_FLAG_SRIOV_ENABLED;

	return 0;
}