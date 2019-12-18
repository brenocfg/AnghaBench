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
struct uath_softc {int /*<<< orphan*/  sc_dev; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UATH_ASSERT_LOCKED (struct uath_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int uath_flush (struct uath_softc*) ; 
 int uath_reset_tx_queues (struct uath_softc*) ; 
 int uath_set_chan (struct uath_softc*,struct ieee80211_channel*) ; 
 int uath_set_ledstate (struct uath_softc*,int /*<<< orphan*/ ) ; 
 int uath_wme_init (struct uath_softc*) ; 

__attribute__((used)) static int
uath_switch_channel(struct uath_softc *sc, struct ieee80211_channel *c)
{
	int error;

	UATH_ASSERT_LOCKED(sc);

	/* set radio frequency */
	error = uath_set_chan(sc, c);
	if (error) {
		device_printf(sc->sc_dev,
		    "could not set channel, error %d\n", error);
		goto failed;
	}
	/* reset Tx rings */
	error = uath_reset_tx_queues(sc);
	if (error) {
		device_printf(sc->sc_dev,
		    "could not reset Tx queues, error %d\n", error);
		goto failed;
	}
	/* set Tx rings WME properties */
	error = uath_wme_init(sc);
	if (error) {
		device_printf(sc->sc_dev,
		    "could not init Tx queues, error %d\n", error);
		goto failed;
	}
	error = uath_set_ledstate(sc, 0);
	if (error) {
		device_printf(sc->sc_dev,
		    "could not set led state, error %d\n", error);
		goto failed;
	}
	error = uath_flush(sc);
	if (error) {
		device_printf(sc->sc_dev,
		    "could not flush pipes, error %d\n", error);
		goto failed;
	}
failed:
	return (error);
}