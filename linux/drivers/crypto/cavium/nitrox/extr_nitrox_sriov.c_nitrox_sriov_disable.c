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
struct TYPE_2__ {scalar_t__ max_vf_queues; scalar_t__ num_vfs; } ;
struct nitrox_device {int /*<<< orphan*/  mode; TYPE_1__ iov; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV (struct nitrox_device*) ; 
 int EPERM ; 
 int /*<<< orphan*/  __NDEV_MODE_PF ; 
 int /*<<< orphan*/  __NDEV_SRIOV_BIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_nps_core_vfcfg_mode (struct nitrox_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int nitrox_pf_reinit (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_sriov_cleanup (struct nitrox_device*) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 struct nitrox_device* pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ pci_vfs_assigned (struct pci_dev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nitrox_sriov_disable(struct pci_dev *pdev)
{
	struct nitrox_device *ndev = pci_get_drvdata(pdev);

	if (!test_bit(__NDEV_SRIOV_BIT, &ndev->flags))
		return 0;

	if (pci_vfs_assigned(pdev)) {
		dev_warn(DEV(ndev), "VFs are attached to VM. Can't disable SR-IOV\n");
		return -EPERM;
	}
	pci_disable_sriov(pdev);
	/* clear bit in flags */
	clear_bit(__NDEV_SRIOV_BIT, &ndev->flags);

	ndev->iov.num_vfs = 0;
	ndev->iov.max_vf_queues = 0;
	ndev->mode = __NDEV_MODE_PF;

	/* cleanup PF SR-IOV resources */
	nitrox_sriov_cleanup(ndev);

	config_nps_core_vfcfg_mode(ndev, ndev->mode);

	return nitrox_pf_reinit(ndev);
}