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
struct dme_softc {int /*<<< orphan*/ * dme_macaddr; int /*<<< orphan*/  dme_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DME_PAR (int) ; 
 int ETHER_ADDR_LEN ; 
 char* device_get_name (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  dme_parse_macaddr (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dme_read_reg (struct dme_softc*,int /*<<< orphan*/ ) ; 
 char* kern_getenv (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static void
dme_get_macaddr(struct dme_softc *sc)
{
	char devid_str[32];
	char *var;
	int i;

	/* Cannot use resource_string_value with static hints mode */
	snprintf(devid_str, 32, "hint.%s.%d.macaddr",
	    device_get_name(sc->dme_dev),
	    device_get_unit(sc->dme_dev));

	/* Try resource hints */
	if ((var = kern_getenv(devid_str)) != NULL) {
		if (!dme_parse_macaddr(var, sc->dme_macaddr)) {
			device_printf(sc->dme_dev, "MAC address: %s (hints)\n", var);
			return;
		}
	}

	/*
	 * Try to read MAC address from the device, in case U-Boot has
	 * pre-programmed one for us.
	 */
	for (i = 0; i < ETHER_ADDR_LEN; i++)
		sc->dme_macaddr[i] = dme_read_reg(sc, DME_PAR(i));

	device_printf(sc->dme_dev, "MAC address %6D (existing)\n",
	    sc->dme_macaddr, ":");
}