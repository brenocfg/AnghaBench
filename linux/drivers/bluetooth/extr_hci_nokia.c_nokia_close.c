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
struct nokia_bt_dev {int initialized; TYPE_1__* serdev; int /*<<< orphan*/  wakeup_bt; int /*<<< orphan*/  reset; int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  txq; } ;
struct hci_uart {struct nokia_bt_dev* priv; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nokia_close(struct hci_uart *hu)
{
	struct nokia_bt_dev *btdev = hu->priv;
	struct device *dev = &btdev->serdev->dev;

	dev_dbg(dev, "close device");

	btdev->initialized = false;

	skb_queue_purge(&btdev->txq);

	kfree_skb(btdev->rx_skb);

	/* disable module */
	gpiod_set_value(btdev->reset, 1);
	gpiod_set_value(btdev->wakeup_bt, 0);

	pm_runtime_disable(&btdev->serdev->dev);

	return 0;
}