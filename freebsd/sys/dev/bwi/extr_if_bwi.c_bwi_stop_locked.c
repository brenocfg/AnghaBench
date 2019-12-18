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
struct bwi_softc {int sc_flags; int sc_nmac; int /*<<< orphan*/  sc_watchdog_timer; scalar_t__ sc_tx_timer; struct bwi_mac* sc_mac; TYPE_1__* sc_cur_regwin; scalar_t__ sc_led_blinking; int /*<<< orphan*/  sc_led_blink_ch; int /*<<< orphan*/  sc_calib_ch; } ;
struct bwi_regwin {int dummy; } ;
struct bwi_mac {int mac_flags; struct bwi_regwin mac_regwin; } ;
struct TYPE_2__ {scalar_t__ rw_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_ALL_INTRS ; 
 int /*<<< orphan*/  BWI_ASSERT_LOCKED (struct bwi_softc*) ; 
 int BWI_F_RUNNING ; 
 int BWI_F_STOP ; 
 int BWI_MAC_F_INITED ; 
 int /*<<< orphan*/  BWI_MAC_INTR_MASK ; 
 scalar_t__ BWI_REGWIN_T_MAC ; 
 int /*<<< orphan*/  CSR_READ_4 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bwi_bbp_power_off (struct bwi_softc*) ; 
 int /*<<< orphan*/  bwi_disable_intrs (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_mac_shutdown (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_mac_stop (struct bwi_mac*) ; 
 int bwi_regwin_switch (struct bwi_softc*,struct bwi_regwin*,struct bwi_regwin**) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bwi_stop_locked(struct bwi_softc *sc, int statechg)
{
	struct bwi_mac *mac;
	int i, error, pwr_off = 0;

	BWI_ASSERT_LOCKED(sc);

	callout_stop(&sc->sc_calib_ch);
	callout_stop(&sc->sc_led_blink_ch);
	sc->sc_led_blinking = 0;
	sc->sc_flags |= BWI_F_STOP;

	if (sc->sc_flags & BWI_F_RUNNING) {
		KASSERT(sc->sc_cur_regwin->rw_type == BWI_REGWIN_T_MAC,
		    ("current regwin type %d", sc->sc_cur_regwin->rw_type));
		mac = (struct bwi_mac *)sc->sc_cur_regwin;

		bwi_disable_intrs(sc, BWI_ALL_INTRS);
		CSR_READ_4(sc, BWI_MAC_INTR_MASK);
		bwi_mac_stop(mac);
	}

	for (i = 0; i < sc->sc_nmac; ++i) {
		struct bwi_regwin *old_rw;

		mac = &sc->sc_mac[i];
		if ((mac->mac_flags & BWI_MAC_F_INITED) == 0)
			continue;

		error = bwi_regwin_switch(sc, &mac->mac_regwin, &old_rw);
		if (error)
			continue;

		bwi_mac_shutdown(mac);
		pwr_off = 1;

		bwi_regwin_switch(sc, old_rw, NULL);
	}

	if (pwr_off)
		bwi_bbp_power_off(sc);

	sc->sc_tx_timer = 0;
	callout_stop(&sc->sc_watchdog_timer);
	sc->sc_flags &= ~BWI_F_RUNNING;
}