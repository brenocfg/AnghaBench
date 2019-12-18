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
struct hci_uart {TYPE_1__* proto; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enqueue ) (struct hci_uart*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hci_uart* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_skb_pkt_type (struct sk_buff*) ; 
 int /*<<< orphan*/  hci_uart_tx_wakeup (struct hci_uart*) ; 
 int /*<<< orphan*/  stub1 (struct hci_uart*,struct sk_buff*) ; 

__attribute__((used)) static int hci_uart_send_frame(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_uart *hu = hci_get_drvdata(hdev);

	BT_DBG("%s: type %d len %d", hdev->name, hci_skb_pkt_type(skb),
	       skb->len);

	hu->proto->enqueue(hu, skb);

	hci_uart_tx_wakeup(hu);

	return 0;
}