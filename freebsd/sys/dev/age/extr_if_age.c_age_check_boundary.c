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
struct TYPE_2__ {scalar_t__ age_smb_block_paddr; scalar_t__ age_cmb_block_paddr; scalar_t__ age_rr_ring_paddr; scalar_t__ age_rx_ring_paddr; scalar_t__ age_tx_ring_paddr; } ;
struct age_softc {TYPE_1__ age_rdata; } ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 scalar_t__ AGE_ADDR_HI (scalar_t__) ; 
 scalar_t__ AGE_CMB_BLOCK_SZ ; 
 scalar_t__ AGE_RR_RING_SZ ; 
 scalar_t__ AGE_RX_RING_SZ ; 
 scalar_t__ AGE_SMB_BLOCK_SZ ; 
 scalar_t__ AGE_TX_RING_SZ ; 
 int EFBIG ; 

__attribute__((used)) static int
age_check_boundary(struct age_softc *sc)
{
	bus_addr_t rx_ring_end, rr_ring_end, tx_ring_end;
	bus_addr_t cmb_block_end, smb_block_end;

	/* Tx/Rx descriptor queue should reside within 4GB boundary. */
	tx_ring_end = sc->age_rdata.age_tx_ring_paddr + AGE_TX_RING_SZ;
	rx_ring_end = sc->age_rdata.age_rx_ring_paddr + AGE_RX_RING_SZ;
	rr_ring_end = sc->age_rdata.age_rr_ring_paddr + AGE_RR_RING_SZ;
	cmb_block_end = sc->age_rdata.age_cmb_block_paddr + AGE_CMB_BLOCK_SZ;
	smb_block_end = sc->age_rdata.age_smb_block_paddr + AGE_SMB_BLOCK_SZ;

	if ((AGE_ADDR_HI(tx_ring_end) !=
	    AGE_ADDR_HI(sc->age_rdata.age_tx_ring_paddr)) ||
	    (AGE_ADDR_HI(rx_ring_end) !=
	    AGE_ADDR_HI(sc->age_rdata.age_rx_ring_paddr)) ||
	    (AGE_ADDR_HI(rr_ring_end) !=
	    AGE_ADDR_HI(sc->age_rdata.age_rr_ring_paddr)) ||
	    (AGE_ADDR_HI(cmb_block_end) !=
	    AGE_ADDR_HI(sc->age_rdata.age_cmb_block_paddr)) ||
	    (AGE_ADDR_HI(smb_block_end) !=
	    AGE_ADDR_HI(sc->age_rdata.age_smb_block_paddr)))
		return (EFBIG);

	if ((AGE_ADDR_HI(tx_ring_end) != AGE_ADDR_HI(rx_ring_end)) ||
	    (AGE_ADDR_HI(tx_ring_end) != AGE_ADDR_HI(rr_ring_end)) ||
	    (AGE_ADDR_HI(tx_ring_end) != AGE_ADDR_HI(cmb_block_end)) ||
	    (AGE_ADDR_HI(tx_ring_end) != AGE_ADDR_HI(smb_block_end)))
		return (EFBIG);

	return (0);
}