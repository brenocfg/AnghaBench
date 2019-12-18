#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_2__* dev; scalar_t__ len; } ;
struct dma_desc {int buf1; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int DESC_OWN ; 
 int SWITCH_NUM_PORTS ; 
 int TX_QUEUE_LEN ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/ * adm5120_devs ; 
 int cur_txl ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int dirty_txl ; 
 scalar_t__ netif_running (TYPE_2__*) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_lock ; 
 struct dma_desc* txl_descs ; 
 struct sk_buff** txl_skbuff ; 

__attribute__((used)) static void adm5120_switch_tx(void)
{
	unsigned int entry;

	spin_lock(&tx_lock);
	entry = dirty_txl % TX_RING_SIZE;
	while (dirty_txl != cur_txl) {
		struct dma_desc *desc = &txl_descs[entry];
		struct sk_buff *skb = txl_skbuff[entry];

		if (desc->buf1 & DESC_OWN)
			break;

		if (netif_running(skb->dev)) {
			skb->dev->stats.tx_bytes += skb->len;
			skb->dev->stats.tx_packets++;
		}

		dev_kfree_skb_irq(skb);
		txl_skbuff[entry] = NULL;
		entry = (++dirty_txl) % TX_RING_SIZE;
	}

	if ((cur_txl - dirty_txl) < TX_QUEUE_LEN - 4) {
		int i;
		for (i = 0; i < SWITCH_NUM_PORTS; i++) {
			if (!adm5120_devs[i])
				continue;
			netif_wake_queue(adm5120_devs[i]);
		}
	}
	spin_unlock(&tx_lock);
}