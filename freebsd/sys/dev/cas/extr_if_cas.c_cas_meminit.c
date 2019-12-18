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
struct cas_softc {scalar_t__ sc_rxdptr; scalar_t__ sc_rxcptr; int /*<<< orphan*/ * sc_rxcomps; scalar_t__ sc_txwin; scalar_t__ sc_txnext; int /*<<< orphan*/  sc_txfree; TYPE_1__* sc_txdescs; } ;
struct TYPE_2__ {scalar_t__ cd_buf_ptr; scalar_t__ cd_flags; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CAS_CDSYNC (struct cas_softc*,int) ; 
 int /*<<< orphan*/  CAS_INIT_RXDESC (struct cas_softc*,int,int) ; 
 int /*<<< orphan*/  CAS_LOCK_ASSERT (struct cas_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAS_MAXTXFREE ; 
 int CAS_NRXCOMP ; 
 int CAS_NRXDESC ; 
 int CAS_NTXDESC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  cas_rxcompinit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cas_meminit(struct cas_softc *sc)
{
	int i;

	CAS_LOCK_ASSERT(sc, MA_OWNED);

	/*
	 * Initialize the transmit descriptor ring.
	 */
	for (i = 0; i < CAS_NTXDESC; i++) {
		sc->sc_txdescs[i].cd_flags = 0;
		sc->sc_txdescs[i].cd_buf_ptr = 0;
	}
	sc->sc_txfree = CAS_MAXTXFREE;
	sc->sc_txnext = 0;
	sc->sc_txwin = 0;

	/*
	 * Initialize the receive completion ring.
	 */
	for (i = 0; i < CAS_NRXCOMP; i++)
		cas_rxcompinit(&sc->sc_rxcomps[i]);
	sc->sc_rxcptr = 0;

	/*
	 * Initialize the first receive descriptor ring.  We leave
	 * the second one zeroed as we don't actually use it.
	 */
	for (i = 0; i < CAS_NRXDESC; i++)
		CAS_INIT_RXDESC(sc, i, i);
	sc->sc_rxdptr = 0;

	CAS_CDSYNC(sc, BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
}