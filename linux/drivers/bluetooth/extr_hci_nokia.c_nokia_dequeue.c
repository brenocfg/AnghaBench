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
struct sk_buff {int dummy; } ;
struct nokia_bt_dev {int tx_enabled; int /*<<< orphan*/  wakeup_bt; TYPE_1__* serdev; int /*<<< orphan*/  initialized; int /*<<< orphan*/  txq; } ;
struct hci_uart {struct nokia_bt_dev* priv; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  serdev_device_wait_until_sent (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *nokia_dequeue(struct hci_uart *hu)
{
	struct nokia_bt_dev *btdev = hu->priv;
	struct device *dev = &btdev->serdev->dev;
	struct sk_buff *result = skb_dequeue(&btdev->txq);

	if (!btdev->initialized)
		return result;

	if (btdev->tx_enabled == !!result)
		return result;

	if (result) {
		pm_runtime_get_sync(dev);
		gpiod_set_value_cansleep(btdev->wakeup_bt, 1);
	} else {
		serdev_device_wait_until_sent(btdev->serdev, 0);
		gpiod_set_value_cansleep(btdev->wakeup_bt, 0);
		pm_runtime_put(dev);
	}

	btdev->tx_enabled = !!result;

	return result;
}