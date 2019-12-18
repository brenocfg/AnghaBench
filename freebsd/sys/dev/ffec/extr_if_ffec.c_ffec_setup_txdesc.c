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
typedef  scalar_t__ uint32_t ;
struct ffec_softc {TYPE_1__* txdesc_ring; int /*<<< orphan*/  txcount; } ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_2__ {scalar_t__ flags_len; scalar_t__ buf_paddr; } ;

/* Variables and functions */
 scalar_t__ FEC_TXDESC_L ; 
 scalar_t__ FEC_TXDESC_READY ; 
 scalar_t__ FEC_TXDESC_TC ; 
 scalar_t__ FEC_TXDESC_WRAP ; 
 scalar_t__ next_txidx (struct ffec_softc*,int) ; 

__attribute__((used)) inline static uint32_t
ffec_setup_txdesc(struct ffec_softc *sc, int idx, bus_addr_t paddr, 
    uint32_t len)
{
	uint32_t nidx;
	uint32_t flags;

	nidx = next_txidx(sc, idx);

	/* Addr/len 0 means we're clearing the descriptor after xmit done. */
	if (paddr == 0 || len == 0) {
		flags = 0;
		--sc->txcount;
	} else {
		flags = FEC_TXDESC_READY | FEC_TXDESC_L | FEC_TXDESC_TC;
		++sc->txcount;
	}
	if (nidx == 0)
		flags |= FEC_TXDESC_WRAP;

	/*
	 * The hardware requires 32-bit physical addresses.  We set up the dma
	 * tag to indicate that, so the cast to uint32_t should never lose
	 * significant bits.
	 */
	sc->txdesc_ring[idx].buf_paddr = (uint32_t)paddr;
	sc->txdesc_ring[idx].flags_len = flags | len; /* Must be set last! */

	return (nidx);
}