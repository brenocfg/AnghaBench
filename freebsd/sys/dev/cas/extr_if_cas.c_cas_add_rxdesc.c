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
typedef  size_t u_int ;
struct cas_softc {int sc_rxdptr; TYPE_1__* sc_rxdsoft; int /*<<< orphan*/  sc_rdmatag; } ;
struct TYPE_2__ {int /*<<< orphan*/  rxds_dmamap; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CAS_CDSYNC (struct cas_softc*,int) ; 
 int /*<<< orphan*/  CAS_LOCK_ASSERT (struct cas_softc*,int /*<<< orphan*/ ) ; 
 int CAS_NEXTRXDESC (int) ; 
 int CAS_NRXDESC ; 
 int CAS_NRXDESC_MASK ; 
 int /*<<< orphan*/  CAS_RX_KICK ; 
 int /*<<< orphan*/  CAS_UPDATE_RXDESC (struct cas_softc*,int,size_t) ; 
 int /*<<< orphan*/  CAS_WRITE_4 (struct cas_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
cas_add_rxdesc(struct cas_softc *sc, u_int idx)
{

	CAS_LOCK_ASSERT(sc, MA_OWNED);

	bus_dmamap_sync(sc->sc_rdmatag, sc->sc_rxdsoft[idx].rxds_dmamap,
	    BUS_DMASYNC_PREREAD);
	CAS_UPDATE_RXDESC(sc, sc->sc_rxdptr, idx);
	sc->sc_rxdptr = CAS_NEXTRXDESC(sc->sc_rxdptr);

	/*
	 * Update the RX kick register.  This register has to point to the
	 * descriptor after the last valid one (before the current batch)
	 * and for optimum performance should be incremented in multiples
	 * of 4 (the DMA engine fetches/updates descriptors in batches of 4).
	 */
	if ((sc->sc_rxdptr % 4) == 0) {
		CAS_CDSYNC(sc, BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		CAS_WRITE_4(sc, CAS_RX_KICK,
		    (sc->sc_rxdptr + CAS_NRXDESC - 4) & CAS_NRXDESC_MASK);
	}
}