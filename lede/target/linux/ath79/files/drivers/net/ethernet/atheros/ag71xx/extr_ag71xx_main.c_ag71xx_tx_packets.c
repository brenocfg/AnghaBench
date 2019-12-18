#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct ag71xx_ring {int dirty; int curr; TYPE_1__* buf; int /*<<< orphan*/  order; } ;
struct ag71xx_desc {int /*<<< orphan*/  ctrl; } ;
struct ag71xx {int /*<<< orphan*/  restart_work; TYPE_3__* dev; scalar_t__ tx_hang_workaround; struct ag71xx_ring tx_ring; } ;
struct TYPE_6__ {int tx_bytes; int tx_packets; } ;
struct TYPE_7__ {TYPE_2__ stats; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {scalar_t__ len; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_TX_STATUS ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DESC_EMPTY ; 
 int HZ ; 
 int /*<<< orphan*/  TX_STATUS_PS ; 
 scalar_t__ ag71xx_check_dma_stuck (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_desc_empty (struct ag71xx_desc*) ; 
 struct ag71xx_desc* ag71xx_ring_desc (struct ag71xx_ring*,unsigned int) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_completed_queue (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ag71xx_tx_packets(struct ag71xx *ag, bool flush)
{
	struct ag71xx_ring *ring = &ag->tx_ring;
	bool dma_stuck = false;
	int ring_mask = BIT(ring->order) - 1;
	int ring_size = BIT(ring->order);
	int sent = 0;
	int bytes_compl = 0;
	int n = 0;

	DBG("%s: processing TX ring\n", ag->dev->name);

	while (ring->dirty + n != ring->curr) {
		unsigned int i = (ring->dirty + n) & ring_mask;
		struct ag71xx_desc *desc = ag71xx_ring_desc(ring, i);
		struct sk_buff *skb = ring->buf[i].skb;

		if (!flush && !ag71xx_desc_empty(desc)) {
			if (ag->tx_hang_workaround &&
			    ag71xx_check_dma_stuck(ag)) {
				schedule_delayed_work(&ag->restart_work, HZ / 2);
				dma_stuck = true;
			}
			break;
		}

		if (flush)
			desc->ctrl |= DESC_EMPTY;

		n++;
		if (!skb)
			continue;

		dev_kfree_skb_any(skb);
		ring->buf[i].skb = NULL;

		bytes_compl += ring->buf[i].len;

		sent++;
		ring->dirty += n;

		while (n > 0) {
			ag71xx_wr(ag, AG71XX_REG_TX_STATUS, TX_STATUS_PS);
			n--;
		}
	}

	DBG("%s: %d packets sent out\n", ag->dev->name, sent);

	if (!sent)
		return 0;

	ag->dev->stats.tx_bytes += bytes_compl;
	ag->dev->stats.tx_packets += sent;

	netdev_completed_queue(ag->dev, sent, bytes_compl);
	if ((ring->curr - ring->dirty) < (ring_size * 3) / 4)
		netif_wake_queue(ag->dev);

	if (!dma_stuck)
		cancel_delayed_work(&ag->restart_work);

	return sent;
}