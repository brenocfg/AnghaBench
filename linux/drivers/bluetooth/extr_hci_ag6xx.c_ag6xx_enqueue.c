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
struct sk_buff {int dummy; } ;
struct hci_uart {struct ag6xx_data* priv; } ;
struct ag6xx_data {int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int ag6xx_enqueue(struct hci_uart *hu, struct sk_buff *skb)
{
	struct ag6xx_data *ag6xx = hu->priv;

	skb_queue_tail(&ag6xx->txq, skb);
	return 0;
}