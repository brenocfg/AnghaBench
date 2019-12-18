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
typedef  scalar_t__ usb_error_t ;
typedef  int uint32_t ;
struct urtw_softc {int sc_flags; scalar_t__ (* sc_rf_set_chan ) (struct urtw_softc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * sc_curchan; int /*<<< orphan*/  sc_mtx; } ;
struct ieee80211com {int /*<<< orphan*/ * ic_curchan; struct urtw_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_ATIM_TR_ITV ; 
 int /*<<< orphan*/  URTW_ATIM_WND ; 
 int /*<<< orphan*/  URTW_BEACON_INTERVAL ; 
 int /*<<< orphan*/  URTW_BEACON_INTERVAL_TIME ; 
 int /*<<< orphan*/  URTW_LOCK (struct urtw_softc*) ; 
 int URTW_RUNNING ; 
 int /*<<< orphan*/  URTW_TX_CONF ; 
 int URTW_TX_LOOPBACK_MAC ; 
 int URTW_TX_LOOPBACK_MASK ; 
 int /*<<< orphan*/  URTW_UNLOCK (struct urtw_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_chan2ieee (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct urtw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urtw_read32_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  urtw_write16_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  urtw_write32_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
urtw_set_channel(struct ieee80211com *ic)
{
	struct urtw_softc *sc = ic->ic_softc;
	uint32_t data, orig;
	usb_error_t error;

	/*
	 * if the user set a channel explicitly using ifconfig(8) this function
	 * can be called earlier than we're expected that in some cases the
	 * initialization would be failed if setting a channel is called before
	 * the init have done.
	 */
	if (!(sc->sc_flags & URTW_RUNNING))
		return;

	if (sc->sc_curchan != NULL && sc->sc_curchan == ic->ic_curchan)
		return;

	URTW_LOCK(sc);

	/*
	 * during changing th channel we need to temporarily be disable 
	 * TX.
	 */
	urtw_read32_m(sc, URTW_TX_CONF, &orig);
	data = orig & ~URTW_TX_LOOPBACK_MASK;
	urtw_write32_m(sc, URTW_TX_CONF, data | URTW_TX_LOOPBACK_MAC);

	error = sc->sc_rf_set_chan(sc, ieee80211_chan2ieee(ic, ic->ic_curchan));
	if (error != 0)
		goto fail;
	usb_pause_mtx(&sc->sc_mtx, 10);
	urtw_write32_m(sc, URTW_TX_CONF, orig);

	urtw_write16_m(sc, URTW_ATIM_WND, 2);
	urtw_write16_m(sc, URTW_ATIM_TR_ITV, 100);
	urtw_write16_m(sc, URTW_BEACON_INTERVAL, 100);
	urtw_write16_m(sc, URTW_BEACON_INTERVAL_TIME, 100);

fail:
	URTW_UNLOCK(sc);

	sc->sc_curchan = ic->ic_curchan;

	if (error != 0)
		device_printf(sc->sc_dev, "could not change the channel\n");
}