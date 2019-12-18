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
struct mrvl_data {int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  rawq; int /*<<< orphan*/  txq; } ;
struct hci_uart {struct mrvl_data* priv; scalar_t__ serdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int /*<<< orphan*/  kfree (struct mrvl_data*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serdev_device_close (scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mrvl_close(struct hci_uart *hu)
{
	struct mrvl_data *mrvl = hu->priv;

	BT_DBG("hu %p", hu);

	if (hu->serdev)
		serdev_device_close(hu->serdev);

	skb_queue_purge(&mrvl->txq);
	skb_queue_purge(&mrvl->rawq);
	kfree_skb(mrvl->rx_skb);
	kfree(mrvl);

	hu->priv = NULL;
	return 0;
}