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
struct pci_dev {int dummy; } ;
struct amb_dev {int /*<<< orphan*/  atm_dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  housekeeping; } ;

/* Variables and functions */
 int DBG_INFO ; 
 int DBG_INIT ; 
 int /*<<< orphan*/  PRINTD (int,char*,struct amb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amb_reset (struct amb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atm_dev_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_queues (struct amb_dev*) ; 
 int /*<<< orphan*/  drain_rx_pools (struct amb_dev*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct amb_dev*) ; 
 int /*<<< orphan*/  interrupts_off (struct amb_dev*) ; 
 int /*<<< orphan*/  kfree (struct amb_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct amb_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int) ; 

__attribute__((used)) static void amb_remove_one(struct pci_dev *pci_dev)
{
	struct amb_dev *dev;

	dev = pci_get_drvdata(pci_dev);

	PRINTD(DBG_INFO|DBG_INIT, "closing %p (atm_dev = %p)", dev, dev->atm_dev);
	del_timer_sync(&dev->housekeeping);
	// the drain should not be necessary
	drain_rx_pools(dev);
	interrupts_off(dev);
	amb_reset(dev, 0);
	free_irq(dev->irq, dev);
	pci_disable_device(pci_dev);
	destroy_queues(dev);
	atm_dev_deregister(dev->atm_dev);
	kfree(dev);
	pci_release_region(pci_dev, 1);
}