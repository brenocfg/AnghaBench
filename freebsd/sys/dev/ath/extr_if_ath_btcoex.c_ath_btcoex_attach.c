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
struct ath_softc {int /*<<< orphan*/  sc_dev; struct ath_hal* sc_ah; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int ath_btcoex_cfg_wb195 (struct ath_softc*) ; 
 int ath_btcoex_cfg_wb222 (struct ath_softc*) ; 
 int ath_btcoex_cfg_wb225 (struct ath_softc*) ; 
 int ath_btcoex_cfg_wb335b (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_hal_btcoex_supported (struct ath_hal*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int resource_string_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

int
ath_btcoex_attach(struct ath_softc *sc)
{
	int ret;
	struct ath_hal *ah = sc->sc_ah;
	const char *profname;

	/*
	 * No chipset bluetooth coexistence? Then do nothing.
	 */
	if (! ath_hal_btcoex_supported(ah))
		return (0);

	/*
	 * Look at the hints to determine which bluetooth
	 * profile to configure.
	 */
	ret = resource_string_value(device_get_name(sc->sc_dev),
	    device_get_unit(sc->sc_dev),
	    "btcoex_profile",
	    &profname);
	if (ret != 0) {
		/* nothing to do */
		return (0);
	}

	if (strncmp(profname, "wb195", 5) == 0) {
		ret = ath_btcoex_cfg_wb195(sc);
	} else if (strncmp(profname, "wb222", 5) == 0) {
		ret = ath_btcoex_cfg_wb222(sc);
	} else if (strncmp(profname, "wb225", 5) == 0) {
		ret = ath_btcoex_cfg_wb225(sc);
	} else if (strncmp(profname, "wb335", 5) == 0) {
		ret = ath_btcoex_cfg_wb335b(sc);
	} else {
		return (0);
	}

	/*
	 * Propagate up failure from the actual attach phase.
	 */
	if (ret != 0)
		return (ret);

	return (0);
}