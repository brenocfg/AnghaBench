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
struct nokia_bt_dev {int /*<<< orphan*/  txq; TYPE_1__* serdev; } ;
struct hci_uart {struct nokia_bt_dev* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nokia_flush(struct hci_uart *hu)
{
	struct nokia_bt_dev *btdev = hu->priv;

	dev_dbg(&btdev->serdev->dev, "flush device");

	skb_queue_purge(&btdev->txq);

	return 0;
}