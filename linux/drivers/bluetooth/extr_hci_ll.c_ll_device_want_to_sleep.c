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
struct ll_struct {scalar_t__ hcill_state; int /*<<< orphan*/  hcill_lock; } ;
struct hci_uart {struct ll_struct* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
 scalar_t__ HCILL_ASLEEP ; 
 scalar_t__ HCILL_AWAKE ; 
 int /*<<< orphan*/  HCILL_GO_TO_SLEEP_ACK ; 
 int /*<<< orphan*/  hci_uart_tx_wakeup (struct hci_uart*) ; 
 scalar_t__ send_hcill_cmd (int /*<<< orphan*/ ,struct hci_uart*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ll_device_want_to_sleep(struct hci_uart *hu)
{
	unsigned long flags;
	struct ll_struct *ll = hu->priv;

	BT_DBG("hu %p", hu);

	/* lock hcill state */
	spin_lock_irqsave(&ll->hcill_lock, flags);

	/* sanity check */
	if (ll->hcill_state != HCILL_AWAKE)
		BT_ERR("ERR: HCILL_GO_TO_SLEEP_IND in state %ld",
		       ll->hcill_state);

	/* acknowledge device sleep */
	if (send_hcill_cmd(HCILL_GO_TO_SLEEP_ACK, hu) < 0) {
		BT_ERR("cannot acknowledge device sleep");
		goto out;
	}

	/* update state */
	ll->hcill_state = HCILL_ASLEEP;

out:
	spin_unlock_irqrestore(&ll->hcill_lock, flags);

	/* actually send the sleep ack packet */
	hci_uart_tx_wakeup(hu);
}