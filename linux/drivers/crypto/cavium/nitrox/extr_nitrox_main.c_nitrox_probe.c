#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  revision; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct TYPE_4__ {int /*<<< orphan*/  dropped; int /*<<< orphan*/  completed; int /*<<< orphan*/  posted; } ;
struct TYPE_3__ {int /*<<< orphan*/  revision_id; int /*<<< orphan*/  device_id; int /*<<< orphan*/  vendor_id; } ;
struct nitrox_device {scalar_t__ node; int /*<<< orphan*/  state; TYPE_2__ stats; int /*<<< orphan*/  qlen; int /*<<< orphan*/  nr_queues; int /*<<< orphan*/  bar_addr; int /*<<< orphan*/  timeout; TYPE_1__ hw; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TIMEOUT ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRIVER_VERSION ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_PF_QUEUES ; 
 scalar_t__ NUMA_NO_NODE ; 
 int /*<<< orphan*/  __NDEV_NOT_READY ; 
 int /*<<< orphan*/  __NDEV_READY ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info_once (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_to_node (int /*<<< orphan*/ *) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nitrox_device*) ; 
 struct nitrox_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_add_to_devlist (struct nitrox_device*) ; 
 int nitrox_crypto_register () ; 
 int /*<<< orphan*/  nitrox_debugfs_exit (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_debugfs_init (struct nitrox_device*) ; 
 int nitrox_device_flr (struct pci_dev*) ; 
 int /*<<< orphan*/  nitrox_driver_name ; 
 int nitrox_pf_hw_init (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_pf_sw_cleanup (struct nitrox_device*) ; 
 int nitrox_pf_sw_init (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_remove_from_devlist (struct nitrox_device*) ; 
 int /*<<< orphan*/  num_online_cpus () ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device_mem (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int pci_request_mem_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct nitrox_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  qlen ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int nitrox_probe(struct pci_dev *pdev,
			const struct pci_device_id *id)
{
	struct nitrox_device *ndev;
	int err;

	dev_info_once(&pdev->dev, "%s driver version %s\n",
		      nitrox_driver_name, DRIVER_VERSION);

	err = pci_enable_device_mem(pdev);
	if (err)
		return err;

	/* do FLR */
	err = nitrox_device_flr(pdev);
	if (err) {
		dev_err(&pdev->dev, "FLR failed\n");
		pci_disable_device(pdev);
		return err;
	}

	if (!dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64))) {
		dev_dbg(&pdev->dev, "DMA to 64-BIT address\n");
	} else {
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		if (err) {
			dev_err(&pdev->dev, "DMA configuration failed\n");
			pci_disable_device(pdev);
			return err;
		}
	}

	err = pci_request_mem_regions(pdev, nitrox_driver_name);
	if (err) {
		pci_disable_device(pdev);
		return err;
	}
	pci_set_master(pdev);

	ndev = kzalloc(sizeof(*ndev), GFP_KERNEL);
	if (!ndev) {
		err = -ENOMEM;
		goto ndev_fail;
	}

	pci_set_drvdata(pdev, ndev);
	ndev->pdev = pdev;

	/* add to device list */
	nitrox_add_to_devlist(ndev);

	ndev->hw.vendor_id = pdev->vendor;
	ndev->hw.device_id = pdev->device;
	ndev->hw.revision_id = pdev->revision;
	/* command timeout in jiffies */
	ndev->timeout = msecs_to_jiffies(CMD_TIMEOUT);
	ndev->node = dev_to_node(&pdev->dev);
	if (ndev->node == NUMA_NO_NODE)
		ndev->node = 0;

	ndev->bar_addr = ioremap(pci_resource_start(pdev, 0),
				 pci_resource_len(pdev, 0));
	if (!ndev->bar_addr) {
		err = -EIO;
		goto ioremap_err;
	}
	/* allocate command queus based on cpus, max queues are 64 */
	ndev->nr_queues = min_t(u32, MAX_PF_QUEUES, num_online_cpus());
	ndev->qlen = qlen;

	err = nitrox_pf_sw_init(ndev);
	if (err)
		goto ioremap_err;

	err = nitrox_pf_hw_init(ndev);
	if (err)
		goto pf_hw_fail;

	nitrox_debugfs_init(ndev);

	/* clear the statistics */
	atomic64_set(&ndev->stats.posted, 0);
	atomic64_set(&ndev->stats.completed, 0);
	atomic64_set(&ndev->stats.dropped, 0);

	atomic_set(&ndev->state, __NDEV_READY);
	/* barrier to sync with other cpus */
	smp_mb__after_atomic();

	err = nitrox_crypto_register();
	if (err)
		goto crypto_fail;

	return 0;

crypto_fail:
	nitrox_debugfs_exit(ndev);
	atomic_set(&ndev->state, __NDEV_NOT_READY);
	/* barrier to sync with other cpus */
	smp_mb__after_atomic();
pf_hw_fail:
	nitrox_pf_sw_cleanup(ndev);
ioremap_err:
	nitrox_remove_from_devlist(ndev);
	kfree(ndev);
	pci_set_drvdata(pdev, NULL);
ndev_fail:
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
	return err;
}