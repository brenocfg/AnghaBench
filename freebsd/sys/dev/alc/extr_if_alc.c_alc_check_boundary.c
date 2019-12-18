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
struct TYPE_2__ {scalar_t__ alc_tx_ring_paddr; scalar_t__ alc_cmb_paddr; scalar_t__ alc_rr_ring_paddr; scalar_t__ alc_rx_ring_paddr; } ;
struct alc_softc {TYPE_1__ alc_rdata; } ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 scalar_t__ ALC_ADDR_HI (scalar_t__) ; 
 scalar_t__ ALC_CMB_SZ ; 
 scalar_t__ ALC_RR_RING_SZ ; 
 scalar_t__ ALC_RX_RING_SZ ; 
 scalar_t__ ALC_TX_RING_SZ ; 
 int EFBIG ; 

__attribute__((used)) static int
alc_check_boundary(struct alc_softc *sc)
{
	bus_addr_t cmb_end, rx_ring_end, rr_ring_end, tx_ring_end;

	rx_ring_end = sc->alc_rdata.alc_rx_ring_paddr + ALC_RX_RING_SZ;
	rr_ring_end = sc->alc_rdata.alc_rr_ring_paddr + ALC_RR_RING_SZ;
	cmb_end = sc->alc_rdata.alc_cmb_paddr + ALC_CMB_SZ;
	tx_ring_end = sc->alc_rdata.alc_tx_ring_paddr + ALC_TX_RING_SZ;

	/* 4GB boundary crossing is not allowed. */
	if ((ALC_ADDR_HI(rx_ring_end) !=
	    ALC_ADDR_HI(sc->alc_rdata.alc_rx_ring_paddr)) ||
	    (ALC_ADDR_HI(rr_ring_end) !=
	    ALC_ADDR_HI(sc->alc_rdata.alc_rr_ring_paddr)) ||
	    (ALC_ADDR_HI(cmb_end) !=
	    ALC_ADDR_HI(sc->alc_rdata.alc_cmb_paddr)) ||
	    (ALC_ADDR_HI(tx_ring_end) !=
	    ALC_ADDR_HI(sc->alc_rdata.alc_tx_ring_paddr)))
		return (EFBIG);
	/*
	 * Make sure Rx return descriptor/Rx descriptor/CMB use
	 * the same high address.
	 */
	if ((ALC_ADDR_HI(rx_ring_end) != ALC_ADDR_HI(rr_ring_end)) ||
	    (ALC_ADDR_HI(rx_ring_end) != ALC_ADDR_HI(cmb_end)))
		return (EFBIG);

	return (0);
}