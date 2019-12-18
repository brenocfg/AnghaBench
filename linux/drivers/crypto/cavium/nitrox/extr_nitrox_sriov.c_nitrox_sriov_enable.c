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
struct TYPE_2__ {int num_vfs; int /*<<< orphan*/  max_vf_queues; } ;
struct nitrox_device {int /*<<< orphan*/  mode; TYPE_1__ iov; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV (struct nitrox_device*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  __NDEV_MODE_PF ; 
 int /*<<< orphan*/  __NDEV_SRIOV_BIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_nps_core_vfcfg_mode (struct nitrox_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nitrox_pf_cleanup (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_pf_reinit (struct nitrox_device*) ; 
 int nitrox_sriov_init (struct nitrox_device*) ; 
 int /*<<< orphan*/  num_vfs_to_mode (int) ; 
 int /*<<< orphan*/  num_vfs_valid (int) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 int pci_enable_sriov (struct pci_dev*,int) ; 
 struct nitrox_device* pci_get_drvdata (struct pci_dev*) ; 
 int pci_num_vf (struct pci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vf_mode_to_nr_queues (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nitrox_sriov_enable(struct pci_dev *pdev, int num_vfs)
{
	struct nitrox_device *ndev = pci_get_drvdata(pdev);
	int err;

	if (!num_vfs_valid(num_vfs)) {
		dev_err(DEV(ndev), "Invalid num_vfs %d\n", num_vfs);
		return -EINVAL;
	}

	if (pci_num_vf(pdev) == num_vfs)
		return num_vfs;

	err = pci_enable_sriov(pdev, num_vfs);
	if (err) {
		dev_err(DEV(ndev), "failed to enable PCI sriov %d\n", err);
		return err;
	}
	dev_info(DEV(ndev), "Enabled VF(s) %d\n", num_vfs);

	ndev->mode = num_vfs_to_mode(num_vfs);
	ndev->iov.num_vfs = num_vfs;
	ndev->iov.max_vf_queues = vf_mode_to_nr_queues(ndev->mode);
	/* set bit in flags */
	set_bit(__NDEV_SRIOV_BIT, &ndev->flags);

	/* cleanup PF resources */
	nitrox_pf_cleanup(ndev);

	/* PF SR-IOV mode initialization */
	err = nitrox_sriov_init(ndev);
	if (err)
		goto iov_fail;

	config_nps_core_vfcfg_mode(ndev, ndev->mode);
	return num_vfs;

iov_fail:
	pci_disable_sriov(pdev);
	/* clear bit in flags */
	clear_bit(__NDEV_SRIOV_BIT, &ndev->flags);
	ndev->iov.num_vfs = 0;
	ndev->mode = __NDEV_MODE_PF;
	/* reset back to working mode in PF */
	nitrox_pf_reinit(ndev);
	return err;
}