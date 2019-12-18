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
struct sk_buff {int dummy; } ;
struct hci_uart {struct bcm_data* priv; } ;
struct bcm_device {int /*<<< orphan*/  dev; } ;
struct bcm_data {int /*<<< orphan*/  txq; struct bcm_device* dev; } ;

/* Variables and functions */
 scalar_t__ bcm_device_exists (struct bcm_device*) ; 
 int /*<<< orphan*/  bcm_device_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *bcm_dequeue(struct hci_uart *hu)
{
	struct bcm_data *bcm = hu->priv;
	struct sk_buff *skb = NULL;
	struct bcm_device *bdev = NULL;

	mutex_lock(&bcm_device_lock);

	if (bcm_device_exists(bcm->dev)) {
		bdev = bcm->dev;
		pm_runtime_get_sync(bdev->dev);
		/* Shall be resumed here */
	}

	skb = skb_dequeue(&bcm->txq);

	if (bdev) {
		pm_runtime_mark_last_busy(bdev->dev);
		pm_runtime_put_autosuspend(bdev->dev);
	}

	mutex_unlock(&bcm_device_lock);

	return skb;
}