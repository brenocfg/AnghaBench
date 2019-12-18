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
struct TYPE_4__ {TYPE_1__* ale_rx_page; scalar_t__ ale_tx_cmb_paddr; scalar_t__ ale_tx_ring_paddr; } ;
struct ale_softc {TYPE_2__ ale_cdata; scalar_t__ ale_pagesize; } ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_3__ {scalar_t__ cmb_paddr; scalar_t__ page_paddr; } ;

/* Variables and functions */
 scalar_t__ ALE_ADDR_HI (scalar_t__) ; 
 scalar_t__ ALE_RX_CMB_SZ ; 
 int ALE_RX_PAGES ; 
 scalar_t__ ALE_TX_CMB_SZ ; 
 scalar_t__ ALE_TX_RING_SZ ; 
 int EFBIG ; 

__attribute__((used)) static int
ale_check_boundary(struct ale_softc *sc)
{
	bus_addr_t rx_cmb_end[ALE_RX_PAGES], tx_cmb_end;
	bus_addr_t rx_page_end[ALE_RX_PAGES], tx_ring_end;

	rx_page_end[0] = sc->ale_cdata.ale_rx_page[0].page_paddr +
	    sc->ale_pagesize;
	rx_page_end[1] = sc->ale_cdata.ale_rx_page[1].page_paddr +
	    sc->ale_pagesize;
	tx_ring_end = sc->ale_cdata.ale_tx_ring_paddr + ALE_TX_RING_SZ;
	tx_cmb_end = sc->ale_cdata.ale_tx_cmb_paddr + ALE_TX_CMB_SZ;
	rx_cmb_end[0] = sc->ale_cdata.ale_rx_page[0].cmb_paddr + ALE_RX_CMB_SZ;
	rx_cmb_end[1] = sc->ale_cdata.ale_rx_page[1].cmb_paddr + ALE_RX_CMB_SZ;

	if ((ALE_ADDR_HI(tx_ring_end) !=
	    ALE_ADDR_HI(sc->ale_cdata.ale_tx_ring_paddr)) ||
	    (ALE_ADDR_HI(rx_page_end[0]) !=
	    ALE_ADDR_HI(sc->ale_cdata.ale_rx_page[0].page_paddr)) ||
	    (ALE_ADDR_HI(rx_page_end[1]) !=
	    ALE_ADDR_HI(sc->ale_cdata.ale_rx_page[1].page_paddr)) ||
	    (ALE_ADDR_HI(tx_cmb_end) !=
	    ALE_ADDR_HI(sc->ale_cdata.ale_tx_cmb_paddr)) ||
	    (ALE_ADDR_HI(rx_cmb_end[0]) !=
	    ALE_ADDR_HI(sc->ale_cdata.ale_rx_page[0].cmb_paddr)) ||
	    (ALE_ADDR_HI(rx_cmb_end[1]) !=
	    ALE_ADDR_HI(sc->ale_cdata.ale_rx_page[1].cmb_paddr)))
		return (EFBIG);

	if ((ALE_ADDR_HI(tx_ring_end) != ALE_ADDR_HI(rx_page_end[0])) ||
	    (ALE_ADDR_HI(tx_ring_end) != ALE_ADDR_HI(rx_page_end[1])) ||
	    (ALE_ADDR_HI(tx_ring_end) != ALE_ADDR_HI(rx_cmb_end[0])) ||
	    (ALE_ADDR_HI(tx_ring_end) != ALE_ADDR_HI(rx_cmb_end[1])) ||
	    (ALE_ADDR_HI(tx_ring_end) != ALE_ADDR_HI(tx_cmb_end)))
		return (EFBIG);

	return (0);
}