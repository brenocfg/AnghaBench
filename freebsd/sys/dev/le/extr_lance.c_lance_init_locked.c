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
typedef  int u_long ;
struct lance_softc {int sc_conf3; int sc_addr; int (* sc_rdcsr ) (struct lance_softc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sc_hwinit ) (struct lance_softc*) ;int /*<<< orphan*/  (* sc_start_locked ) (struct lance_softc*) ;int /*<<< orphan*/  sc_wdog_ch; scalar_t__ sc_wdog_timer; int /*<<< orphan*/  (* sc_wrcsr ) (struct lance_softc*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* sc_meminit ) (struct lance_softc*) ;int /*<<< orphan*/  sc_enaddr; int /*<<< orphan*/  (* sc_mediachange ) (struct lance_softc*) ;int /*<<< orphan*/  (* sc_hwreset ) (struct lance_softc*) ;struct ifnet* sc_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int LE_C0_IDON ; 
 int LE_C0_INEA ; 
 int LE_C0_INIT ; 
 int LE_C0_STOP ; 
 int LE_C0_STRT ; 
 int /*<<< orphan*/  LE_CSR0 ; 
 int /*<<< orphan*/  LE_CSR1 ; 
 int /*<<< orphan*/  LE_CSR2 ; 
 int /*<<< orphan*/  LE_CSR3 ; 
 int LE_INITADDR (struct lance_softc*) ; 
 int /*<<< orphan*/  LE_LOCK_ASSERT (struct lance_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lance_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  lance_watchdog ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct lance_softc*,int /*<<< orphan*/ ,int) ; 
 int stub10 (struct lance_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (struct lance_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub12 (struct lance_softc*) ; 
 int /*<<< orphan*/  stub13 (struct lance_softc*) ; 
 int /*<<< orphan*/  stub2 (struct lance_softc*) ; 
 int /*<<< orphan*/  stub3 (struct lance_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct lance_softc*) ; 
 int /*<<< orphan*/  stub5 (struct lance_softc*) ; 
 int /*<<< orphan*/  stub6 (struct lance_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct lance_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct lance_softc*,int /*<<< orphan*/ ,int) ; 
 int stub9 (struct lance_softc*,int /*<<< orphan*/ ) ; 

void
lance_init_locked(struct lance_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;
	u_long a;
	int timo;

	LE_LOCK_ASSERT(sc, MA_OWNED);

	(*sc->sc_wrcsr)(sc, LE_CSR0, LE_C0_STOP);
	DELAY(100);

	/* Newer LANCE chips have a reset register. */
	if (sc->sc_hwreset)
		(*sc->sc_hwreset)(sc);

	/* Set the correct byte swapping mode, etc. */
	(*sc->sc_wrcsr)(sc, LE_CSR3, sc->sc_conf3);

	/* Set the current media. This may require the chip to be stopped. */
	if (sc->sc_mediachange)
		(void)(*sc->sc_mediachange)(sc);

	/*
	 * Update our private copy of the Ethernet address.
	 * We NEED the copy so we can ensure its alignment!
	 */
	memcpy(sc->sc_enaddr, IF_LLADDR(ifp), ETHER_ADDR_LEN);

	/* Set up LANCE init block. */
	(*sc->sc_meminit)(sc);

	/* Give LANCE the physical address of its init block. */
	a = sc->sc_addr + LE_INITADDR(sc);
	(*sc->sc_wrcsr)(sc, LE_CSR1, a & 0xffff);
	(*sc->sc_wrcsr)(sc, LE_CSR2, a >> 16);

	/* Try to initialize the LANCE. */
	DELAY(100);
	(*sc->sc_wrcsr)(sc, LE_CSR0, LE_C0_INIT);

	/* Wait for initialization to finish. */
	for (timo = 100000; timo; timo--)
		if ((*sc->sc_rdcsr)(sc, LE_CSR0) & LE_C0_IDON)
			break;

	if ((*sc->sc_rdcsr)(sc, LE_CSR0) & LE_C0_IDON) {
		/* Start the LANCE. */
		(*sc->sc_wrcsr)(sc, LE_CSR0, LE_C0_INEA | LE_C0_STRT);
		ifp->if_drv_flags |= IFF_DRV_RUNNING;
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		sc->sc_wdog_timer = 0;
		callout_reset(&sc->sc_wdog_ch, hz, lance_watchdog, sc);
		(*sc->sc_start_locked)(sc);
	} else
		if_printf(ifp, "controller failed to initialize\n");

	if (sc->sc_hwinit)
		(*sc->sc_hwinit)(sc);
}