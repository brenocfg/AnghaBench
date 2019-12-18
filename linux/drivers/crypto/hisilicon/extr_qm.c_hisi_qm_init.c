#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct pci_dev {scalar_t__ is_physfn; struct device dev; } ;
struct hisi_qm {int ver; int /*<<< orphan*/  io_base; scalar_t__ use_dma_api; int /*<<< orphan*/  qps_lock; int /*<<< orphan*/  mailbox_lock; TYPE_1__* ops; struct pci_dev* pdev; int /*<<< orphan*/  dev_name; } ;
struct TYPE_3__ {unsigned int (* get_irq_num ) (struct hisi_qm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PCI_BAR_2 ; 
 int /*<<< orphan*/  PCI_IRQ_MSI ; 
#define  QM_HW_V1 129 
#define  QM_HW_V2 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int pci_alloc_irq_vectors (struct pci_dev*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device_mem (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int pci_request_mem_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 TYPE_1__ qm_hw_ops_v1 ; 
 TYPE_1__ qm_hw_ops_v2 ; 
 int qm_irq_register (struct hisi_qm*) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 unsigned int stub1 (struct hisi_qm*) ; 

int hisi_qm_init(struct hisi_qm *qm)
{
	struct pci_dev *pdev = qm->pdev;
	struct device *dev = &pdev->dev;
	unsigned int num_vec;
	int ret;

	switch (qm->ver) {
	case QM_HW_V1:
		qm->ops = &qm_hw_ops_v1;
		break;
	case QM_HW_V2:
		qm->ops = &qm_hw_ops_v2;
		break;
	default:
		return -EINVAL;
	}

	ret = pci_enable_device_mem(pdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to enable device mem!\n");
		return ret;
	}

	ret = pci_request_mem_regions(pdev, qm->dev_name);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to request mem regions!\n");
		goto err_disable_pcidev;
	}

	qm->io_base = ioremap(pci_resource_start(pdev, PCI_BAR_2),
			      pci_resource_len(qm->pdev, PCI_BAR_2));
	if (!qm->io_base) {
		ret = -EIO;
		goto err_release_mem_regions;
	}

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
	if (ret < 0)
		goto err_iounmap;
	pci_set_master(pdev);

	if (!qm->ops->get_irq_num) {
		ret = -EOPNOTSUPP;
		goto err_iounmap;
	}
	num_vec = qm->ops->get_irq_num(qm);
	ret = pci_alloc_irq_vectors(pdev, num_vec, num_vec, PCI_IRQ_MSI);
	if (ret < 0) {
		dev_err(dev, "Failed to enable MSI vectors!\n");
		goto err_iounmap;
	}

	ret = qm_irq_register(qm);
	if (ret)
		goto err_free_irq_vectors;

	mutex_init(&qm->mailbox_lock);
	rwlock_init(&qm->qps_lock);

	dev_dbg(dev, "init qm %s with %s\n", pdev->is_physfn ? "pf" : "vf",
		qm->use_dma_api ? "dma api" : "iommu api");

	return 0;

err_free_irq_vectors:
	pci_free_irq_vectors(pdev);
err_iounmap:
	iounmap(qm->io_base);
err_release_mem_regions:
	pci_release_mem_regions(pdev);
err_disable_pcidev:
	pci_disable_device(pdev);

	return ret;
}