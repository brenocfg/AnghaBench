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
struct ll_struct {int hcill_state; int /*<<< orphan*/  hcill_lock; } ;
struct hci_uart {struct ll_struct* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
#define  HCILL_ASLEEP 129 
#define  HCILL_ASLEEP_TO_AWAKE 128 
 int /*<<< orphan*/  HCILL_WAKE_UP_ACK ; 
 int /*<<< orphan*/  __ll_do_awake (struct ll_struct*) ; 
 int /*<<< orphan*/  hci_uart_tx_wakeup (struct hci_uart*) ; 
 int /*<<< orphan*/  send_hcill_cmd (int /*<<< orphan*/ ,struct hci_uart*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ll_device_want_to_wakeup(struct hci_uart *hu)
{
	unsigned long flags;
	struct ll_struct *ll = hu->priv;

	BT_DBG("hu %p", hu);

	/* lock hcill state */
	spin_lock_irqsave(&ll->hcill_lock, flags);

	switch (ll->hcill_state) {
	case HCILL_ASLEEP_TO_AWAKE:
		/*
		 * This state means that both the host and the BRF chip
		 * have simultaneously sent a wake-up-indication packet.
		 * Traditionally, in this case, receiving a wake-up-indication
		 * was enough and an additional wake-up-ack wasn't needed.
		 * This has changed with the BRF6350, which does require an
		 * explicit wake-up-ack. Other BRF versions, which do not
		 * require an explicit ack here, do accept it, thus it is
		 * perfectly safe to always send one.
		 */
		BT_DBG("dual wake-up-indication");
		/* fall through */
	case HCILL_ASLEEP:
		/* acknowledge device wake up */
		if (send_hcill_cmd(HCILL_WAKE_UP_ACK, hu) < 0) {
			BT_ERR("cannot acknowledge device wake up");
			goto out;
		}
		break;
	default:
		/* any other state is illegal */
		BT_ERR("received HCILL_WAKE_UP_IND in state %ld",
		       ll->hcill_state);
		break;
	}

	/* send pending packets and change state to HCILL_AWAKE */
	__ll_do_awake(ll);

out:
	spin_unlock_irqrestore(&ll->hcill_lock, flags);

	/* actually send the packets */
	hci_uart_tx_wakeup(hu);
}