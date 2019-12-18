#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bwi_ring_data {int /*<<< orphan*/  rdata_desc; } ;
struct bwi_softc {struct bwi_ring_data sc_rx_rdata; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int BWI_RX_NDESC ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bwi_setup_desc32 (struct bwi_softc*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwi_setup_rx_desc32(struct bwi_softc *sc, int buf_idx, bus_addr_t paddr,
		    int buf_len)
{
	struct bwi_ring_data *rd = &sc->sc_rx_rdata;

	KASSERT(buf_idx < BWI_RX_NDESC, ("buf_idx %d", buf_idx));
	bwi_setup_desc32(sc, rd->rdata_desc, BWI_RX_NDESC, buf_idx,
			 paddr, buf_len, 0);
}