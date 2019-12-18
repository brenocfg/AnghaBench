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
struct pci_device_id {int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct eni_zero {int /*<<< orphan*/  dma; int /*<<< orphan*/  addr; } ;
struct eni_dev {struct atm_dev* more; int /*<<< orphan*/  asic; struct pci_dev* pci_dev; struct eni_zero zero; } ;
struct atm_dev {struct eni_dev* dev_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_LABEL ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  ENI_ZEROES_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atm_dev_deregister (struct atm_dev*) ; 
 struct atm_dev* atm_dev_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct atm_dev* eni_boards ; 
 int eni_do_init (struct atm_dev*) ; 
 int /*<<< orphan*/  eni_do_release (struct atm_dev*) ; 
 int eni_start (struct atm_dev*) ; 
 int /*<<< orphan*/  kfree (struct eni_dev*) ; 
 struct eni_dev* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ops ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct atm_dev*) ; 

__attribute__((used)) static int eni_init_one(struct pci_dev *pci_dev,
			const struct pci_device_id *ent)
{
	struct atm_dev *dev;
	struct eni_dev *eni_dev;
	struct eni_zero *zero;
	int rc;

	rc = pci_enable_device(pci_dev);
	if (rc < 0)
		goto out;

	rc = dma_set_mask_and_coherent(&pci_dev->dev, DMA_BIT_MASK(32));
	if (rc < 0)
		goto out;

	rc = -ENOMEM;
	eni_dev = kmalloc(sizeof(struct eni_dev), GFP_KERNEL);
	if (!eni_dev)
		goto err_disable;

	zero = &eni_dev->zero;
	zero->addr = dma_alloc_coherent(&pci_dev->dev,
					ENI_ZEROES_SIZE, &zero->dma, GFP_KERNEL);
	if (!zero->addr)
		goto err_kfree;

	dev = atm_dev_register(DEV_LABEL, &pci_dev->dev, &ops, -1, NULL);
	if (!dev)
		goto err_free_consistent;

	dev->dev_data = eni_dev;
	pci_set_drvdata(pci_dev, dev);
	eni_dev->pci_dev = pci_dev;
	eni_dev->asic = ent->driver_data;

	rc = eni_do_init(dev);
	if (rc < 0)
		goto err_unregister;

	rc = eni_start(dev);
	if (rc < 0)
		goto err_eni_release;

	eni_dev->more = eni_boards;
	eni_boards = dev;
out:
	return rc;

err_eni_release:
	eni_do_release(dev);
err_unregister:
	atm_dev_deregister(dev);
err_free_consistent:
	dma_free_coherent(&pci_dev->dev, ENI_ZEROES_SIZE, zero->addr, zero->dma);
err_kfree:
	kfree(eni_dev);
err_disable:
	pci_disable_device(pci_dev);
	goto out;
}