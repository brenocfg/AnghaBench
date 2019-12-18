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
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 char* device_get_name (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  freeenv (char*) ; 
 char* kern_getenv (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ath_fetch_mac_kenv(struct ath_softc *sc, uint8_t *macaddr)
{
	char devid_str[32];
	int local_mac = 0;
	char *local_macstr;

	/*
	 * Fetch from the kenv rather than using hints.
	 *
	 * Hints would be nice but the transition to dynamic
	 * hints/kenv doesn't happen early enough for this
	 * to work reliably (eg on anything embedded.)
	 */
	snprintf(devid_str, 32, "hint.%s.%d.macaddr",
	    device_get_name(sc->sc_dev),
	    device_get_unit(sc->sc_dev));

	if ((local_macstr = kern_getenv(devid_str)) != NULL) {
		uint32_t tmpmac[ETHER_ADDR_LEN];
		int count;
		int i;

		/* Have a MAC address; should use it */
		device_printf(sc->sc_dev,
		    "Overriding MAC address from environment: '%s'\n",
		    local_macstr);

		/* Extract out the MAC address */
		count = sscanf(local_macstr, "%x%*c%x%*c%x%*c%x%*c%x%*c%x",
		    &tmpmac[0], &tmpmac[1],
		    &tmpmac[2], &tmpmac[3],
		    &tmpmac[4], &tmpmac[5]);
		if (count == 6) {
			/* Valid! */
			local_mac = 1;
			for (i = 0; i < ETHER_ADDR_LEN; i++)
				macaddr[i] = tmpmac[i];
		}
		/* Done! */
		freeenv(local_macstr);
		local_macstr = NULL;
	}

	if (local_mac)
		return (0);
	return (-1);
}