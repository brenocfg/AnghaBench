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
typedef  int uint32_t ;
struct dwc_softc {scalar_t__ mactype; TYPE_1__* rxdesc_ring; scalar_t__ rxdesc_ring_paddr; } ;
struct dwc_hwdesc {int dummy; } ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_2__ {int addr; int tdes1; int /*<<< orphan*/  tdes0; scalar_t__ addr_next; } ;

/* Variables and functions */
 int DDESC_CNTL_CHAINED ; 
 int /*<<< orphan*/  DDESC_RDES0_OWN ; 
 int DDESC_RDES1_CHAINED ; 
 scalar_t__ DWC_GMAC_ALT_DESC ; 
 int MCLBYTES ; 
 int RX_MAX_PACKET ; 
 int next_rxidx (struct dwc_softc*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) inline static uint32_t
dwc_setup_rxdesc(struct dwc_softc *sc, int idx, bus_addr_t paddr)
{
	uint32_t nidx;

	sc->rxdesc_ring[idx].addr = (uint32_t)paddr;
	nidx = next_rxidx(sc, idx);
	sc->rxdesc_ring[idx].addr_next = sc->rxdesc_ring_paddr +	\
	    (nidx * sizeof(struct dwc_hwdesc));
	if (sc->mactype == DWC_GMAC_ALT_DESC)
		sc->rxdesc_ring[idx].tdes1 = DDESC_CNTL_CHAINED | RX_MAX_PACKET;
	else
		sc->rxdesc_ring[idx].tdes1 = DDESC_RDES1_CHAINED | MCLBYTES;

	wmb();
	sc->rxdesc_ring[idx].tdes0 = DDESC_RDES0_OWN;
	wmb();

	return (nidx);
}