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
struct hci_uart {struct bcm_data* priv; int /*<<< orphan*/  hdev; scalar_t__ serdev; } ;
struct bcm_device {scalar_t__ irq; int /*<<< orphan*/  dev; int /*<<< orphan*/ * hu; } ;
struct bcm_data {int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  txq; struct bcm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ bcm_device_exists (struct bcm_device*) ; 
 int /*<<< orphan*/  bcm_device_lock ; 
 int bcm_gpio_set_power (struct bcm_device*,int) ; 
 int /*<<< orphan*/  bt_dev_dbg (int /*<<< orphan*/ ,char*,struct hci_uart*) ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,scalar_t__,struct bcm_device*) ; 
 int /*<<< orphan*/  kfree (struct bcm_data*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ ) ; 
 struct bcm_device* serdev_device_get_drvdata (scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm_close(struct hci_uart *hu)
{
	struct bcm_data *bcm = hu->priv;
	struct bcm_device *bdev = NULL;
	int err;

	bt_dev_dbg(hu->hdev, "hu %p", hu);

	/* Protect bcm->dev against removal of the device or driver */
	mutex_lock(&bcm_device_lock);

	if (hu->serdev) {
		bdev = serdev_device_get_drvdata(hu->serdev);
	} else if (bcm_device_exists(bcm->dev)) {
		bdev = bcm->dev;
#ifdef CONFIG_PM
		bdev->hu = NULL;
#endif
	}

	if (bdev) {
		if (IS_ENABLED(CONFIG_PM) && bdev->irq > 0) {
			devm_free_irq(bdev->dev, bdev->irq, bdev);
			device_init_wakeup(bdev->dev, false);
			pm_runtime_disable(bdev->dev);
		}

		err = bcm_gpio_set_power(bdev, false);
		if (err)
			bt_dev_err(hu->hdev, "Failed to power down");
		else
			pm_runtime_set_suspended(bdev->dev);
	}
	mutex_unlock(&bcm_device_lock);

	skb_queue_purge(&bcm->txq);
	kfree_skb(bcm->rx_skb);
	kfree(bcm);

	hu->priv = NULL;
	return 0;
}