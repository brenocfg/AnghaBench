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
typedef  int uint32_t ;
struct nfe_softc {scalar_t__ nfe_framesize; int /*<<< orphan*/  nfe_int_task; int /*<<< orphan*/  nfe_tq; int /*<<< orphan*/  nfe_irq_status; int /*<<< orphan*/  nfe_process_limit; int /*<<< orphan*/  nfe_ifp; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct nfe_softc*,char*) ; 
 int /*<<< orphan*/  DPRINTFN (struct nfe_softc*,int,char*,int) ; 
 scalar_t__ ETHER_HDR_LEN ; 
 int IFCAP_POLLING ; 
 int IFF_DRV_RUNNING ; 
 scalar_t__ MCLBYTES ; 
 int NFE_IRQ_LINK ; 
 int /*<<< orphan*/  NFE_LOCK (struct nfe_softc*) ; 
 int /*<<< orphan*/  NFE_PHY_STATUS ; 
 scalar_t__ NFE_READ (struct nfe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFE_UNLOCK (struct nfe_softc*) ; 
 int /*<<< orphan*/  NFE_WRITE (struct nfe_softc*,int /*<<< orphan*/ ,int) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sendq_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfe_disable_intr (struct nfe_softc*) ; 
 int /*<<< orphan*/  nfe_enable_intr (struct nfe_softc*) ; 
 int nfe_jrxeof (struct nfe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nfe_rxeof (struct nfe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfe_start_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfe_txeof (struct nfe_softc*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfe_int_task(void *arg, int pending)
{
	struct nfe_softc *sc = arg;
	if_t ifp = sc->nfe_ifp;
	uint32_t r;
	int domore;

	NFE_LOCK(sc);

	if ((r = NFE_READ(sc, sc->nfe_irq_status)) == 0) {
		nfe_enable_intr(sc);
		NFE_UNLOCK(sc);
		return;	/* not for us */
	}
	NFE_WRITE(sc, sc->nfe_irq_status, r);

	DPRINTFN(sc, 5, "nfe_intr: interrupt register %x\n", r);

#ifdef DEVICE_POLLING
	if (if_getcapenable(ifp) & IFCAP_POLLING) {
		NFE_UNLOCK(sc);
		return;
	}
#endif

	if (r & NFE_IRQ_LINK) {
		NFE_READ(sc, NFE_PHY_STATUS);
		NFE_WRITE(sc, NFE_PHY_STATUS, 0xf);
		DPRINTF(sc, "link state changed\n");
	}

	if ((if_getdrvflags(ifp) & IFF_DRV_RUNNING) == 0) {
		NFE_UNLOCK(sc);
		nfe_disable_intr(sc);
		return;
	}

	domore = 0;
	/* check Rx ring */
	if (sc->nfe_framesize > MCLBYTES - ETHER_HDR_LEN)
		domore = nfe_jrxeof(sc, sc->nfe_process_limit, NULL);
	else
		domore = nfe_rxeof(sc, sc->nfe_process_limit, NULL);
	/* check Tx ring */
	nfe_txeof(sc);

	if (!if_sendq_empty(ifp))
		nfe_start_locked(ifp);

	NFE_UNLOCK(sc);

	if (domore || (NFE_READ(sc, sc->nfe_irq_status) != 0)) {
		taskqueue_enqueue(sc->nfe_tq, &sc->nfe_int_task);
		return;
	}

	/* Reenable interrupts. */
	nfe_enable_intr(sc);
}