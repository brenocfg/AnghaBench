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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct hci_uart {int /*<<< orphan*/  proto_lock; TYPE_1__* proto; int /*<<< orphan*/  flags; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enqueue ) (struct hci_uart*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EUNATCH ; 
 int /*<<< orphan*/  HCI_UART_PROTO_READY ; 
 struct hci_uart* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_skb_pkt_type (struct sk_buff*) ; 
 int /*<<< orphan*/  hci_uart_tx_wakeup (struct hci_uart*) ; 
 int /*<<< orphan*/  percpu_down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hci_uart*,struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hci_uart_send_frame(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_uart *hu = hci_get_drvdata(hdev);

	BT_DBG("%s: type %d len %d", hdev->name, hci_skb_pkt_type(skb),
	       skb->len);

	percpu_down_read(&hu->proto_lock);

	if (!test_bit(HCI_UART_PROTO_READY, &hu->flags)) {
		percpu_up_read(&hu->proto_lock);
		return -EUNATCH;
	}

	hu->proto->enqueue(hu, skb);
	percpu_up_read(&hu->proto_lock);

	hci_uart_tx_wakeup(hu);

	return 0;
}