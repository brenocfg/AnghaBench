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
struct qca_serdev {int /*<<< orphan*/  bt_en; int /*<<< orphan*/  btsoc_type; } ;
struct qca_data {int /*<<< orphan*/  rx_skb; int /*<<< orphan*/ * hu; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  wake_retrans_timer; int /*<<< orphan*/  tx_idle_timer; int /*<<< orphan*/  txq; int /*<<< orphan*/  tx_wait_q; } ;
struct hci_uart {struct qca_data* priv; scalar_t__ serdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int /*<<< orphan*/  HCI_IBS_VOTE_STATS_UPDATE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qca_data*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 scalar_t__ qca_is_wcn399x (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qca_power_shutdown (struct hci_uart*) ; 
 struct qca_serdev* serdev_device_get_drvdata (scalar_t__) ; 
 int /*<<< orphan*/  serial_clock_vote (int /*<<< orphan*/ ,struct hci_uart*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qca_close(struct hci_uart *hu)
{
	struct qca_serdev *qcadev;
	struct qca_data *qca = hu->priv;

	BT_DBG("hu %p qca close", hu);

	serial_clock_vote(HCI_IBS_VOTE_STATS_UPDATE, hu);

	skb_queue_purge(&qca->tx_wait_q);
	skb_queue_purge(&qca->txq);
	del_timer(&qca->tx_idle_timer);
	del_timer(&qca->wake_retrans_timer);
	destroy_workqueue(qca->workqueue);
	qca->hu = NULL;

	if (hu->serdev) {
		qcadev = serdev_device_get_drvdata(hu->serdev);
		if (qca_is_wcn399x(qcadev->btsoc_type))
			qca_power_shutdown(hu);
		else
			gpiod_set_value_cansleep(qcadev->bt_en, 0);

	}

	kfree_skb(qca->rx_skb);

	hu->priv = NULL;

	kfree(qca);

	return 0;
}