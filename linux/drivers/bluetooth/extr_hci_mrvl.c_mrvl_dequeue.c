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
struct mrvl_data {int /*<<< orphan*/  rawq; int /*<<< orphan*/  txq; } ;
struct hci_uart {struct mrvl_data* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  pkt_type; } ;

/* Variables and functions */
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *mrvl_dequeue(struct hci_uart *hu)
{
	struct mrvl_data *mrvl = hu->priv;
	struct sk_buff *skb;

	skb = skb_dequeue(&mrvl->txq);
	if (!skb) {
		/* Any raw data ? */
		skb = skb_dequeue(&mrvl->rawq);
	} else {
		/* Prepend skb with frame type */
		memcpy(skb_push(skb, 1), &bt_cb(skb)->pkt_type, 1);
	}

	return skb;
}