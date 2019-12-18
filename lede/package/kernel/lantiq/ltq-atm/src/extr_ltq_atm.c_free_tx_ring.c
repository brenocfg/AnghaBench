#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct connection {int /*<<< orphan*/  lock; struct sk_buff** tx_skb; TYPE_1__* tx_desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  vcc; } ;
struct TYPE_5__ {struct connection* conn; } ;
struct TYPE_4__ {scalar_t__ own; } ;

/* Variables and functions */
 TYPE_3__* ATM_SKB (struct sk_buff*) ; 
 int /*<<< orphan*/  atm_free_tx_skb_vcc (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int dma_tx_descriptor_length ; 
 TYPE_2__ g_atm_priv_data ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_tx_ring(unsigned int queue)
{
	unsigned long flags;
	int i;
	struct connection *conn = &g_atm_priv_data.conn[queue];
	struct sk_buff *skb;

	if (!conn)
		return;

	spin_lock_irqsave(&conn->lock, flags);

	for (i = 0; i < dma_tx_descriptor_length; i++) {
		if (conn->tx_desc[i].own == 0 && conn->tx_skb[i] != NULL) {
			skb = conn->tx_skb[i];
			conn->tx_skb[i] = NULL;
			atm_free_tx_skb_vcc(skb, ATM_SKB(skb)->vcc);
		}
	}
	spin_unlock_irqrestore(&conn->lock, flags);
}