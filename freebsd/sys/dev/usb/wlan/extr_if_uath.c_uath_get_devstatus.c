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
typedef  int /*<<< orphan*/  uint8_t ;
struct uath_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * sc_serial; } ;

/* Variables and functions */
 int IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  ST_MAC_ADDR ; 
 int /*<<< orphan*/  ST_SERIAL_NUMBER ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int uath_get_status (struct uath_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
uath_get_devstatus(struct uath_softc *sc, uint8_t macaddr[IEEE80211_ADDR_LEN])
{
	int error;

	/* retrieve MAC address */
	error = uath_get_status(sc, ST_MAC_ADDR, macaddr, IEEE80211_ADDR_LEN);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not read MAC address\n");
		return (error);
	}

	error = uath_get_status(sc, ST_SERIAL_NUMBER,
	    &sc->sc_serial[0], sizeof(sc->sc_serial));
	if (error != 0) {
		device_printf(sc->sc_dev,
		    "could not read device serial number\n");
		return (error);
	}
	return (0);
}