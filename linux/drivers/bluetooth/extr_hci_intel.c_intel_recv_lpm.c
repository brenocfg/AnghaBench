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
struct sk_buff {scalar_t__ data; } ;
struct intel_data {int /*<<< orphan*/  flags; } ;
struct hci_uart {int /*<<< orphan*/  hdev; struct intel_data* priv; } ;
struct hci_lpm_pkt {int opcode; int dlen; int /*<<< orphan*/ * data; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
#define  LPM_OP_RESUME_ACK 130 
#define  LPM_OP_SUSPEND_ACK 129 
#define  LPM_OP_TX_NOTIFY 128 
 int /*<<< orphan*/  STATE_LPM_TRANSACTION ; 
 int /*<<< orphan*/  STATE_SUSPENDED ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,...) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hci_uart* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  intel_recv_lpm_notify (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_recv_lpm(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_lpm_pkt *lpm = (void *)skb->data;
	struct hci_uart *hu = hci_get_drvdata(hdev);
	struct intel_data *intel = hu->priv;

	switch (lpm->opcode) {
	case LPM_OP_TX_NOTIFY:
		if (lpm->dlen < 1) {
			bt_dev_err(hu->hdev, "Invalid LPM notification packet");
			break;
		}
		intel_recv_lpm_notify(hdev, lpm->data[0]);
		break;
	case LPM_OP_SUSPEND_ACK:
		set_bit(STATE_SUSPENDED, &intel->flags);
		if (test_and_clear_bit(STATE_LPM_TRANSACTION, &intel->flags))
			wake_up_bit(&intel->flags, STATE_LPM_TRANSACTION);
		break;
	case LPM_OP_RESUME_ACK:
		clear_bit(STATE_SUSPENDED, &intel->flags);
		if (test_and_clear_bit(STATE_LPM_TRANSACTION, &intel->flags))
			wake_up_bit(&intel->flags, STATE_LPM_TRANSACTION);
		break;
	default:
		bt_dev_err(hdev, "Unknown LPM opcode (%02x)", lpm->opcode);
		break;
	}

	kfree_skb(skb);

	return 0;
}