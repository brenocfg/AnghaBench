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
struct sk_buff {int dummy; } ;
struct hci_uart {struct sk_buff* tx_skb; int /*<<< orphan*/  proto_lock; TYPE_1__* proto; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct sk_buff* (* dequeue ) (struct hci_uart*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_UART_PROTO_READY ; 
 int /*<<< orphan*/  percpu_down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_read (int /*<<< orphan*/ *) ; 
 struct sk_buff* stub1 (struct hci_uart*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct sk_buff *hci_uart_dequeue(struct hci_uart *hu)
{
	struct sk_buff *skb = hu->tx_skb;

	if (!skb) {
		percpu_down_read(&hu->proto_lock);

		if (test_bit(HCI_UART_PROTO_READY, &hu->flags))
			skb = hu->proto->dequeue(hu);

		percpu_up_read(&hu->proto_lock);
	} else {
		hu->tx_skb = NULL;
	}

	return skb;
}