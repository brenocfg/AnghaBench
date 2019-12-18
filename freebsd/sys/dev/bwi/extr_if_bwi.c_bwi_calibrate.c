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
struct TYPE_4__ {scalar_t__ ic_opmode; } ;
struct bwi_softc {int /*<<< orphan*/  sc_calib_ch; int /*<<< orphan*/  sc_txpwrcb_type; TYPE_1__* sc_cur_regwin; TYPE_2__ sc_ic; } ;
struct bwi_mac {int dummy; } ;
struct TYPE_3__ {scalar_t__ rw_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_ASSERT_LOCKED (struct bwi_softc*) ; 
 scalar_t__ BWI_REGWIN_T_MAC ; 
 int /*<<< orphan*/  BWI_TXPWR_CALIB ; 
 scalar_t__ IEEE80211_M_MONITOR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bwi_mac_calibrate_txpower (struct bwi_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct bwi_softc*) ; 
 int hz ; 

__attribute__((used)) static void
bwi_calibrate(void *xsc)
{
	struct bwi_softc *sc = xsc;
	struct bwi_mac *mac;

	BWI_ASSERT_LOCKED(sc);

	KASSERT(sc->sc_ic.ic_opmode != IEEE80211_M_MONITOR,
	    ("opmode %d", sc->sc_ic.ic_opmode));

	KASSERT(sc->sc_cur_regwin->rw_type == BWI_REGWIN_T_MAC,
	    ("current regwin type %d", sc->sc_cur_regwin->rw_type));
	mac = (struct bwi_mac *)sc->sc_cur_regwin;

	bwi_mac_calibrate_txpower(mac, sc->sc_txpwrcb_type);
	sc->sc_txpwrcb_type = BWI_TXPWR_CALIB;

	/* XXX 15 seconds */
	callout_reset(&sc->sc_calib_ch, hz * 15, bwi_calibrate, sc);
}