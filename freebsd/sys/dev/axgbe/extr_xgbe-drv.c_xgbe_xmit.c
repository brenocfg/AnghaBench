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
struct xgbe_packet_data {int /*<<< orphan*/  rdesc_count; } ;
struct xgbe_ring {struct xgbe_packet_data packet_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  link; } ;
struct xgbe_desc_if {int /*<<< orphan*/  (* map_tx_skb ) (struct xgbe_channel*,struct mbuf*) ;} ;
struct xgbe_hw_if {int /*<<< orphan*/  (* dev_xmit ) (struct xgbe_channel*) ;} ;
struct xgbe_prv_data {struct xgbe_channel* channel; TYPE_1__ phy; int /*<<< orphan*/  dev_state; struct xgbe_desc_if desc_if; struct xgbe_hw_if hw_if; } ;
struct xgbe_channel {struct xgbe_ring* tx_ring; } ;
struct mbuf {int /*<<< orphan*/ * m_nextpkt; } ;
struct ifnet {struct xgbe_prv_data* if_softc; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int /*<<< orphan*/  XGBE_DOWN ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  memset (struct xgbe_packet_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_channel*,struct mbuf*) ; 
 int /*<<< orphan*/  stub2 (struct xgbe_channel*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xgbe_maybe_stop_tx_queue (struct xgbe_channel*,struct xgbe_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_packet_info (struct xgbe_prv_data*,struct xgbe_ring*,struct mbuf*,struct xgbe_packet_data*) ; 

int xgbe_xmit(struct ifnet *ifp, struct mbuf *m)
{
	struct xgbe_prv_data *pdata = ifp->if_softc;
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	struct xgbe_desc_if *desc_if = &pdata->desc_if;
	struct xgbe_channel *channel;
	struct xgbe_ring *ring;
	struct xgbe_packet_data *packet;
	int ret;

	M_ASSERTPKTHDR(m);
	MPASS(m->m_nextpkt == NULL);

	if (__predict_false(test_bit(XGBE_DOWN, &pdata->dev_state) ||
	    !pdata->phy.link)) {
		m_freem(m);
		return (ENETDOWN);
	}

	channel = pdata->channel;
	ring = channel->tx_ring;
	packet = &ring->packet_data;

	/* Calculate preliminary packet info */
	memset(packet, 0, sizeof(*packet));
	xgbe_packet_info(pdata, ring, m, packet);

	/* Check that there are enough descriptors available */
	ret = xgbe_maybe_stop_tx_queue(channel, ring, packet->rdesc_count);
	if (ret)
		goto tx_netdev_return;

	if (!desc_if->map_tx_skb(channel, m)) {
		goto tx_netdev_return;
	}

	/* Configure required descriptor fields for transmission */
	hw_if->dev_xmit(channel);

	return 0;

tx_netdev_return:
	m_free(m);

	return 0;
}