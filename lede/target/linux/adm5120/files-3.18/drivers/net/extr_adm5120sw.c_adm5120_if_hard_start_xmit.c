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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {int /*<<< orphan*/  trans_start; TYPE_1__ stats; int /*<<< orphan*/  name; } ;
struct dma_desc {int buf1; int misc; int buflen; } ;
struct adm5120_if_priv {int vlan_no; } ;

/* Variables and functions */
 unsigned long DESC_ADDR (int /*<<< orphan*/ ) ; 
 unsigned long DESC_EOR ; 
 int DESC_OWN ; 
 int DESC_PKTLEN_SHIFT ; 
 int ETH_ZLEN ; 
 int /*<<< orphan*/  SEND_TRIG_STL ; 
 int SWITCH_NUM_PORTS ; 
 int /*<<< orphan*/  SWITCH_REG_SEND_TRIG ; 
 int /*<<< orphan*/  SW_DBG (char*,int /*<<< orphan*/ ) ; 
 unsigned int TX_QUEUE_LEN ; 
 unsigned int TX_RING_SIZE ; 
 int /*<<< orphan*/ * adm5120_devs ; 
 unsigned int cur_txl ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 unsigned int dirty_txl ; 
 int /*<<< orphan*/  jiffies ; 
 struct adm5120_if_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sw_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_lock ; 
 struct dma_desc* txl_descs ; 
 struct sk_buff** txl_skbuff ; 

__attribute__((used)) static int adm5120_if_hard_start_xmit(struct sk_buff *skb,
		struct net_device *dev)
{
	struct dma_desc *desc;
	struct adm5120_if_priv *priv = netdev_priv(dev);
	unsigned int entry;
	unsigned long data;
	int i;

	/* lock switch irq */
	spin_lock_irq(&tx_lock);

	/* calculate the next TX descriptor entry. */
	entry = cur_txl % TX_RING_SIZE;

	desc = &txl_descs[entry];
	if (desc->buf1 & DESC_OWN) {
		/* We want to write a packet but the TX queue is still
		 * occupied by the DMA. We are faster than the DMA... */
		SW_DBG("%s unable to transmit, packet dopped\n", dev->name);
		dev_kfree_skb(skb);
		dev->stats.tx_dropped++;
		return 0;
	}

	txl_skbuff[entry] = skb;
	data = (desc->buf1 & DESC_EOR);
	data |= DESC_ADDR(skb->data);

	desc->misc =
	    ((skb->len < ETH_ZLEN ? ETH_ZLEN : skb->len) << DESC_PKTLEN_SHIFT) |
	    (0x1 << priv->vlan_no);

	desc->buflen = skb->len < ETH_ZLEN ? ETH_ZLEN : skb->len;

	desc->buf1 = data | DESC_OWN;
	sw_write_reg(SWITCH_REG_SEND_TRIG, SEND_TRIG_STL);

	cur_txl++;
	if (cur_txl == dirty_txl + TX_QUEUE_LEN) {
		for (i = 0; i < SWITCH_NUM_PORTS; i++) {
			if (!adm5120_devs[i])
				continue;
			netif_stop_queue(adm5120_devs[i]);
		}
	}

	dev->trans_start = jiffies;

	spin_unlock_irq(&tx_lock);

	return 0;
}