#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  iobase; int /*<<< orphan*/  irq; int /*<<< orphan*/  atm_dev; int /*<<< orphan*/  housekeeping; } ;
typedef  TYPE_1__ hrz_dev ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_INFO ; 
 int /*<<< orphan*/  HRZ_IO_EXTENT ; 
 int /*<<< orphan*/  PRINTD (int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atm_dev_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  hrz_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 TYPE_1__* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hrz_remove_one(struct pci_dev *pci_dev)
{
	hrz_dev *dev;

	dev = pci_get_drvdata(pci_dev);

	PRINTD(DBG_INFO, "closing %p (atm_dev = %p)", dev, dev->atm_dev);
	del_timer_sync(&dev->housekeeping);
	hrz_reset(dev);
	atm_dev_deregister(dev->atm_dev);
	free_irq(dev->irq, dev);
	release_region(dev->iobase, HRZ_IO_EXTENT);
	kfree(dev);

	pci_disable_device(pci_dev);
}