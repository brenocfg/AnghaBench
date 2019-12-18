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
struct qca_data {int rx_ibs_state; int /*<<< orphan*/  hci_ibs_lock; int /*<<< orphan*/  ibs_sent_wacks; int /*<<< orphan*/  ws_awake_rx; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  ibs_recv_wakes; } ;
struct hci_uart {struct qca_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
#define  HCI_IBS_RX_ASLEEP 129 
#define  HCI_IBS_RX_AWAKE 128 
 int /*<<< orphan*/  HCI_IBS_WAKE_ACK ; 
 int /*<<< orphan*/  hci_uart_tx_wakeup (struct hci_uart*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_hci_ibs_cmd (int /*<<< orphan*/ ,struct hci_uart*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void device_want_to_wakeup(struct hci_uart *hu)
{
	unsigned long flags;
	struct qca_data *qca = hu->priv;

	BT_DBG("hu %p want to wake up", hu);

	spin_lock_irqsave(&qca->hci_ibs_lock, flags);

	qca->ibs_recv_wakes++;

	switch (qca->rx_ibs_state) {
	case HCI_IBS_RX_ASLEEP:
		/* Make sure clock is on - we may have turned clock off since
		 * receiving the wake up indicator awake rx clock.
		 */
		queue_work(qca->workqueue, &qca->ws_awake_rx);
		spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);
		return;

	case HCI_IBS_RX_AWAKE:
		/* Always acknowledge device wake up,
		 * sending IBS message doesn't count as TX ON.
		 */
		if (send_hci_ibs_cmd(HCI_IBS_WAKE_ACK, hu) < 0) {
			BT_ERR("Failed to acknowledge device wake up");
			break;
		}
		qca->ibs_sent_wacks++;
		break;

	default:
		/* Any other state is illegal */
		BT_ERR("Received HCI_IBS_WAKE_IND in rx state %d",
		       qca->rx_ibs_state);
		break;
	}

	spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);

	/* Actually send the packets */
	hci_uart_tx_wakeup(hu);
}