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
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma; scalar_t__ va; int /*<<< orphan*/  size; } ;
struct hisi_qm {int /*<<< orphan*/  io_base; TYPE_1__ qdma; scalar_t__ use_dma_api; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_qm_cache_wb (struct hisi_qm*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  qm_irq_unregister (struct hisi_qm*) ; 

void hisi_qm_uninit(struct hisi_qm *qm)
{
	struct pci_dev *pdev = qm->pdev;
	struct device *dev = &pdev->dev;

	if (qm->use_dma_api && qm->qdma.va) {
		hisi_qm_cache_wb(qm);
		dma_free_coherent(dev, qm->qdma.size,
				  qm->qdma.va, qm->qdma.dma);
		memset(&qm->qdma, 0, sizeof(qm->qdma));
	}

	qm_irq_unregister(qm);
	pci_free_irq_vectors(pdev);
	iounmap(qm->io_base);
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
}