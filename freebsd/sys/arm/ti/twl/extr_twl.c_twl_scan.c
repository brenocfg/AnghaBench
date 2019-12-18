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
typedef  scalar_t__ uint8_t ;
struct twl_softc {int /*<<< orphan*/  sc_scan_hook; int /*<<< orphan*/  sc_subaddr_map; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ TWL_CHIP_ID0 ; 
 int /*<<< orphan*/  TWL_INVALID_CHIP_ID ; 
 int /*<<< orphan*/  TWL_LOCK (struct twl_softc*) ; 
 int TWL_MAX_SUBADDRS ; 
 int /*<<< orphan*/  TWL_UNLOCK (struct twl_softc*) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 struct twl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ twl_test_present (struct twl_softc*,scalar_t__) ; 

__attribute__((used)) static void
twl_scan(void *dev)
{
	struct twl_softc *sc;
	unsigned i;
	uint8_t devs[TWL_MAX_SUBADDRS];
	uint8_t base = TWL_CHIP_ID0;

	sc = device_get_softc((device_t)dev);

	memset(devs, TWL_INVALID_CHIP_ID, TWL_MAX_SUBADDRS);

	/* Try each of the addresses (0x48, 0x49, 0x4a & 0x4b) to determine which
	 * sub modules we have.
	 */
	for (i = 0; i < TWL_MAX_SUBADDRS; i++) {
		if (twl_test_present(sc, (base + i)) == 0) {
			devs[i] = (base + i);
			device_printf(sc->sc_dev, "Found (sub)device at 0x%02x\n", (base + i));
		}
	}

	TWL_LOCK(sc);
	memcpy(sc->sc_subaddr_map, devs, TWL_MAX_SUBADDRS);
	TWL_UNLOCK(sc);

	/* Finished with the interrupt hook */
	config_intrhook_disestablish(&sc->sc_scan_hook);
}