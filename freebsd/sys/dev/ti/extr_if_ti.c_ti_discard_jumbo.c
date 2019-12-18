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
struct TYPE_4__ {struct ti_rx_desc* ti_rx_jumbo_ring; } ;
struct ti_softc {TYPE_1__* ti_ifp; TYPE_2__ ti_rdata; } ;
struct ti_rx_desc {int ti_flags; int ti_idx; scalar_t__ ti_tcp_udp_cksum; scalar_t__ ti_vlan_tag; int /*<<< orphan*/  ti_type; scalar_t__ ti_len; } ;
struct TYPE_3__ {int if_capenable; } ;

/* Variables and functions */
 scalar_t__ ETHER_ALIGN ; 
 int IFCAP_RXCSUM ; 
 scalar_t__ MJUM9BYTES ; 
 int TI_BDFLAG_IP_CKSUM ; 
 int TI_BDFLAG_JUMBO_RING ; 
 int TI_BDFLAG_TCP_UDP_CKSUM ; 
 int /*<<< orphan*/  TI_BDTYPE_RECV_JUMBO_BD ; 

__attribute__((used)) static void
ti_discard_jumbo(struct ti_softc *sc, int i)
{

	struct ti_rx_desc *r;

	r = &sc->ti_rdata.ti_rx_jumbo_ring[i];
	r->ti_len = MJUM9BYTES - ETHER_ALIGN;
	r->ti_type = TI_BDTYPE_RECV_JUMBO_BD;
	r->ti_flags = TI_BDFLAG_JUMBO_RING;
	r->ti_vlan_tag = 0;
	r->ti_tcp_udp_cksum = 0;
	if (sc->ti_ifp->if_capenable & IFCAP_RXCSUM)
		r->ti_flags |= TI_BDFLAG_TCP_UDP_CKSUM | TI_BDFLAG_IP_CKSUM;
	r->ti_idx = i;
}