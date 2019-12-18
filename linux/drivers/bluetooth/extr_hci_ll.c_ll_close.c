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
struct ll_struct {int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  txq; int /*<<< orphan*/  tx_wait_q; } ;
struct ll_device {int /*<<< orphan*/  ext_clk; int /*<<< orphan*/  enable_gpio; } ;
struct hci_uart {struct ll_struct* priv; scalar_t__ serdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ll_struct*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 struct ll_device* serdev_device_get_drvdata (scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ll_close(struct hci_uart *hu)
{
	struct ll_struct *ll = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&ll->tx_wait_q);
	skb_queue_purge(&ll->txq);

	kfree_skb(ll->rx_skb);

	if (hu->serdev) {
		struct ll_device *lldev = serdev_device_get_drvdata(hu->serdev);

		gpiod_set_value_cansleep(lldev->enable_gpio, 0);

		clk_disable_unprepare(lldev->ext_clk);
	}

	hu->priv = NULL;

	kfree(ll);

	return 0;
}