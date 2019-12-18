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
struct pci_dev {int dummy; } ;
struct driver_data {int /*<<< orphan*/  remove_list; TYPE_2__* work; scalar_t__ isr_workq; int /*<<< orphan*/  dd_flag; int /*<<< orphan*/  queue; TYPE_1__* pdev; int /*<<< orphan*/  irq_workers_active; int /*<<< orphan*/  bdev; int /*<<< orphan*/  sr; int /*<<< orphan*/  online_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  cpu_binding; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int MTIP_ABAR ; 
 int /*<<< orphan*/  MTIP_DDF_REMOVAL_BIT ; 
 int /*<<< orphan*/  MTIP_DDF_REMOVE_PENDING_BIT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_set_queue_dying (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  dev_lock ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  drop_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  fsync_bdev (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree (struct driver_data*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mtip_block_remove (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_check_surprise_removal (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct driver_data* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcim_iounmap_regions (struct pci_dev*,int) ; 
 int /*<<< orphan*/  removing_list ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void mtip_pci_remove(struct pci_dev *pdev)
{
	struct driver_data *dd = pci_get_drvdata(pdev);
	unsigned long flags, to;

	set_bit(MTIP_DDF_REMOVAL_BIT, &dd->dd_flag);

	spin_lock_irqsave(&dev_lock, flags);
	list_del_init(&dd->online_list);
	list_add(&dd->remove_list, &removing_list);
	spin_unlock_irqrestore(&dev_lock, flags);

	mtip_check_surprise_removal(pdev);
	synchronize_irq(dd->pdev->irq);

	/* Spin until workers are done */
	to = jiffies + msecs_to_jiffies(4000);
	do {
		msleep(20);
	} while (atomic_read(&dd->irq_workers_active) != 0 &&
		time_before(jiffies, to));

	if (!dd->sr)
		fsync_bdev(dd->bdev);

	if (atomic_read(&dd->irq_workers_active) != 0) {
		dev_warn(&dd->pdev->dev,
			"Completion workers still active!\n");
	}

	blk_set_queue_dying(dd->queue);
	set_bit(MTIP_DDF_REMOVE_PENDING_BIT, &dd->dd_flag);

	/* Clean up the block layer. */
	mtip_block_remove(dd);

	if (dd->isr_workq) {
		flush_workqueue(dd->isr_workq);
		destroy_workqueue(dd->isr_workq);
		drop_cpu(dd->work[0].cpu_binding);
		drop_cpu(dd->work[1].cpu_binding);
		drop_cpu(dd->work[2].cpu_binding);
	}

	pci_disable_msi(pdev);

	spin_lock_irqsave(&dev_lock, flags);
	list_del_init(&dd->remove_list);
	spin_unlock_irqrestore(&dev_lock, flags);

	kfree(dd);

	pcim_iounmap_regions(pdev, 1 << MTIP_ABAR);
	pci_set_drvdata(pdev, NULL);
}