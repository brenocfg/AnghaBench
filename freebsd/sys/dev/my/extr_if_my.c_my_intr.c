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
typedef  int u_int32_t ;
struct my_softc {struct ifnet* my_ifp; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int CSR_READ_4 (struct my_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct my_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int MY_ETI ; 
 int MY_FBE ; 
 int /*<<< orphan*/  MY_IMR ; 
 int MY_INTRS ; 
 int /*<<< orphan*/  MY_ISR ; 
 int /*<<< orphan*/  MY_LOCK (struct my_softc*) ; 
 int MY_RBU ; 
 int MY_RI ; 
 int MY_RxErr ; 
 int MY_TBU ; 
 int MY_TI ; 
 int /*<<< orphan*/  MY_UNLOCK (struct my_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  my_init_locked (struct my_softc*) ; 
 int /*<<< orphan*/  my_reset (struct my_softc*) ; 
 int /*<<< orphan*/  my_rxeof (struct my_softc*) ; 
 int /*<<< orphan*/  my_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  my_stop (struct my_softc*) ; 
 int /*<<< orphan*/  my_txeoc (struct my_softc*) ; 
 int /*<<< orphan*/  my_txeof (struct my_softc*) ; 

__attribute__((used)) static void
my_intr(void *arg)
{
	struct my_softc *sc;
	struct ifnet   *ifp;
	u_int32_t       status;

	sc = arg;
	MY_LOCK(sc);
	ifp = sc->my_ifp;
	if (!(ifp->if_flags & IFF_UP)) {
		MY_UNLOCK(sc);
		return;
	}
	/* Disable interrupts. */
	CSR_WRITE_4(sc, MY_IMR, 0x00000000);

	for (;;) {
		status = CSR_READ_4(sc, MY_ISR);
		status &= MY_INTRS;
		if (status)
			CSR_WRITE_4(sc, MY_ISR, status);
		else
			break;

		if (status & MY_RI)	/* receive interrupt */
			my_rxeof(sc);

		if ((status & MY_RBU) || (status & MY_RxErr)) {
			/* rx buffer unavailable or rx error */
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
#ifdef foo
			my_stop(sc);
			my_reset(sc);
			my_init_locked(sc);
#endif
		}
		if (status & MY_TI)	/* tx interrupt */
			my_txeof(sc);
		if (status & MY_ETI)	/* tx early interrupt */
			my_txeof(sc);
		if (status & MY_TBU)	/* tx buffer unavailable */
			my_txeoc(sc);

#if 0				/* 90/1/18 delete */
		if (status & MY_FBE) {
			my_reset(sc);
			my_init_locked(sc);
		}
#endif

	}

	/* Re-enable interrupts. */
	CSR_WRITE_4(sc, MY_IMR, MY_INTRS);
	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		my_start_locked(ifp);
	MY_UNLOCK(sc);
	return;
}