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
typedef  scalar_t__ u64 ;
struct i40e_eth_stats {int /*<<< orphan*/  rx_unknown_protocol; scalar_t__ rx_discards; int /*<<< orphan*/  tx_errors; scalar_t__ tx_multicast; scalar_t__ rx_multicast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; scalar_t__ tx_broadcast; scalar_t__ tx_unicast; scalar_t__ rx_broadcast; scalar_t__ rx_unicast; scalar_t__ tx_discards; } ;
struct ixl_vsi {struct i40e_eth_stats eth_stats; struct ifnet* ifp; struct ixl_pf* back; } ;
struct TYPE_2__ {scalar_t__ rx_discards; } ;
struct i40e_hw_port_stats {TYPE_1__ eth; scalar_t__ rx_jabber; scalar_t__ rx_fragments; scalar_t__ rx_oversize; scalar_t__ rx_undersize; scalar_t__ illegal_bytes; scalar_t__ crc_errors; scalar_t__ tx_dropped_link_down; } ;
struct ixl_pf {struct i40e_hw_port_stats stats; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXL_SET_COLLISIONS (struct ixl_vsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXL_SET_IBYTES (struct ixl_vsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXL_SET_IERRORS (struct ixl_vsi*,scalar_t__) ; 
 int /*<<< orphan*/  IXL_SET_IMCASTS (struct ixl_vsi*,scalar_t__) ; 
 int /*<<< orphan*/  IXL_SET_IPACKETS (struct ixl_vsi*,scalar_t__) ; 
 int /*<<< orphan*/  IXL_SET_IQDROPS (struct ixl_vsi*,scalar_t__) ; 
 int /*<<< orphan*/  IXL_SET_NOPROTO (struct ixl_vsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXL_SET_OBYTES (struct ixl_vsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXL_SET_OERRORS (struct ixl_vsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXL_SET_OMCASTS (struct ixl_vsi*,scalar_t__) ; 
 int /*<<< orphan*/  IXL_SET_OPACKETS (struct ixl_vsi*,scalar_t__) ; 
 int /*<<< orphan*/  IXL_SET_OQDROPS (struct ixl_vsi*,scalar_t__) ; 
 int /*<<< orphan*/  ixl_update_eth_stats (struct ixl_vsi*) ; 

void
ixl_update_vsi_stats(struct ixl_vsi *vsi)
{
	struct ixl_pf		*pf;
	struct ifnet		*ifp;
	struct i40e_eth_stats	*es;
	u64			tx_discards;

	struct i40e_hw_port_stats *nsd;

	pf = vsi->back;
	ifp = vsi->ifp;
	es = &vsi->eth_stats;
	nsd = &pf->stats;

	ixl_update_eth_stats(vsi);

	tx_discards = es->tx_discards + nsd->tx_dropped_link_down;

	/* Update ifnet stats */
	IXL_SET_IPACKETS(vsi, es->rx_unicast +
	                   es->rx_multicast +
			   es->rx_broadcast);
	IXL_SET_OPACKETS(vsi, es->tx_unicast +
	                   es->tx_multicast +
			   es->tx_broadcast);
	IXL_SET_IBYTES(vsi, es->rx_bytes);
	IXL_SET_OBYTES(vsi, es->tx_bytes);
	IXL_SET_IMCASTS(vsi, es->rx_multicast);
	IXL_SET_OMCASTS(vsi, es->tx_multicast);

	IXL_SET_IERRORS(vsi, nsd->crc_errors + nsd->illegal_bytes +
	    nsd->rx_undersize + nsd->rx_oversize + nsd->rx_fragments +
	    nsd->rx_jabber);
	IXL_SET_OERRORS(vsi, es->tx_errors);
	IXL_SET_IQDROPS(vsi, es->rx_discards + nsd->eth.rx_discards);
	IXL_SET_OQDROPS(vsi, tx_discards);
	IXL_SET_NOPROTO(vsi, es->rx_unknown_protocol);
	IXL_SET_COLLISIONS(vsi, 0);
}