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
struct timer_list {int dummy; } ;
struct qca_data {int tx_ibs_state; int /*<<< orphan*/  hci_ibs_lock; int /*<<< orphan*/  wake_retrans_timer; int /*<<< orphan*/  wake_retrans; int /*<<< orphan*/  ibs_sent_wakes; struct hci_uart* hu; } ;
struct hci_uart {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*,int) ; 
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
#define  HCI_IBS_TX_ASLEEP 130 
#define  HCI_IBS_TX_AWAKE 129 
#define  HCI_IBS_TX_WAKING 128 
 int /*<<< orphan*/  HCI_IBS_WAKE_IND ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 struct qca_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_uart_tx_wakeup (struct hci_uart*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct qca_data* qca ; 
 int /*<<< orphan*/  send_hci_ibs_cmd (int /*<<< orphan*/ ,struct hci_uart*) ; 
 int /*<<< orphan*/  spin_lock_irqsave_nested (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_retrans_timer ; 

__attribute__((used)) static void hci_ibs_wake_retrans_timeout(struct timer_list *t)
{
	struct qca_data *qca = from_timer(qca, t, wake_retrans_timer);
	struct hci_uart *hu = qca->hu;
	unsigned long flags, retrans_delay;
	bool retransmit = false;

	BT_DBG("hu %p wake retransmit timeout in %d state",
		hu, qca->tx_ibs_state);

	spin_lock_irqsave_nested(&qca->hci_ibs_lock,
				 flags, SINGLE_DEPTH_NESTING);

	switch (qca->tx_ibs_state) {
	case HCI_IBS_TX_WAKING:
		/* No WAKE_ACK, retransmit WAKE */
		retransmit = true;
		if (send_hci_ibs_cmd(HCI_IBS_WAKE_IND, hu) < 0) {
			BT_ERR("Failed to acknowledge device wake up");
			break;
		}
		qca->ibs_sent_wakes++;
		retrans_delay = msecs_to_jiffies(qca->wake_retrans);
		mod_timer(&qca->wake_retrans_timer, jiffies + retrans_delay);
		break;

	case HCI_IBS_TX_ASLEEP:
	case HCI_IBS_TX_AWAKE:
		/* Fall through */

	default:
		BT_ERR("Spurious timeout tx state %d", qca->tx_ibs_state);
		break;
	}

	spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);

	if (retransmit)
		hci_uart_tx_wakeup(hu);
}