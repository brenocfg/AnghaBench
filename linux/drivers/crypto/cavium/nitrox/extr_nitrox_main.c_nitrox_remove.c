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
struct TYPE_2__ {int /*<<< orphan*/  device_id; int /*<<< orphan*/  vendor_id; } ;
struct nitrox_device {int /*<<< orphan*/  bar_addr; int /*<<< orphan*/  state; TYPE_1__ hw; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV (struct nitrox_device*) ; 
 int /*<<< orphan*/  __NDEV_NOT_READY ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_crypto_unregister () ; 
 int /*<<< orphan*/  nitrox_debugfs_exit (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_pf_sw_cleanup (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_remove_from_devlist (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_sriov_configure (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct nitrox_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 

__attribute__((used)) static void nitrox_remove(struct pci_dev *pdev)
{
	struct nitrox_device *ndev = pci_get_drvdata(pdev);

	if (!ndev)
		return;

	if (!refcount_dec_and_test(&ndev->refcnt)) {
		dev_err(DEV(ndev), "Device refcnt not zero (%d)\n",
			refcount_read(&ndev->refcnt));
		return;
	}

	dev_info(DEV(ndev), "Removing Device %x:%x\n",
		 ndev->hw.vendor_id, ndev->hw.device_id);

	atomic_set(&ndev->state, __NDEV_NOT_READY);
	/* barrier to sync with other cpus */
	smp_mb__after_atomic();

	nitrox_remove_from_devlist(ndev);

#ifdef CONFIG_PCI_IOV
	/* disable SR-IOV */
	nitrox_sriov_configure(pdev, 0);
#endif
	nitrox_crypto_unregister();
	nitrox_debugfs_exit(ndev);
	nitrox_pf_sw_cleanup(ndev);

	iounmap(ndev->bar_addr);
	kfree(ndev);

	pci_set_drvdata(pdev, NULL);
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
}