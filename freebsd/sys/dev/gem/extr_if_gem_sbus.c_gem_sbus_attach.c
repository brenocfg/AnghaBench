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
typedef  int /*<<< orphan*/  uint32_t ;
struct gem_softc {int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  sc_ih; int /*<<< orphan*/  sc_enaddr; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_variant; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  GEM_BANK2_READ_4 (struct gem_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BANK2_WRITE_4 (struct gem_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_LOCK_DESTROY (struct gem_softc*) ; 
 int /*<<< orphan*/  GEM_LOCK_INIT (struct gem_softc*,int /*<<< orphan*/ ) ; 
 size_t GEM_RES_INTR ; 
 int /*<<< orphan*/  GEM_SBUS_BIF_RESET ; 
 int /*<<< orphan*/  GEM_SBUS_CFG_64BIT ; 
 int /*<<< orphan*/  GEM_SBUS_CFG_BURST_32 ; 
 int /*<<< orphan*/  GEM_SBUS_CFG_BURST_64 ; 
 int /*<<< orphan*/  GEM_SBUS_CFG_PARITY ; 
 int /*<<< orphan*/  GEM_SBUS_CONFIG ; 
 int /*<<< orphan*/  GEM_SERDES ; 
 int /*<<< orphan*/  GEM_SUN_GEM ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  OF_getetheraddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SBUS_BURST64_MASK ; 
 int SBUS_BURST64_SHIFT ; 
 int SBUS_BURST_32 ; 
 int SBUS_BURST_64 ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gem_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct gem_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gem_attach (struct gem_softc*) ; 
 int /*<<< orphan*/  gem_detach (struct gem_softc*) ; 
 int /*<<< orphan*/  gem_intr ; 
 int /*<<< orphan*/  gem_sbus_res_spec ; 
 int sbus_get_burstsz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gem_sbus_attach(device_t dev)
{
	struct gem_softc *sc;
	int burst;
	uint32_t val;

	sc = device_get_softc(dev);
	sc->sc_variant = GEM_SUN_GEM;
	sc->sc_dev = dev;
	/* All known SBus models use a SERDES. */
	sc->sc_flags = GEM_SERDES;

	if (bus_alloc_resources(dev, gem_sbus_res_spec, sc->sc_res)) {
		device_printf(dev, "failed to allocate resources\n");
		bus_release_resources(dev, gem_sbus_res_spec, sc->sc_res);
		return (ENXIO);
	}

	GEM_LOCK_INIT(sc, device_get_nameunit(dev));

	OF_getetheraddr(dev, sc->sc_enaddr);

	burst = sbus_get_burstsz(dev);
	val = GEM_SBUS_CFG_PARITY;
	if ((burst & SBUS_BURST64_MASK) != 0) {
		val |= GEM_SBUS_CFG_64BIT;
		burst >>= SBUS_BURST64_SHIFT;
	}
	if ((burst & SBUS_BURST_64) != 0)
		val |= GEM_SBUS_CFG_BURST_64;
	else if ((burst & SBUS_BURST_32) != 0)
		val |= GEM_SBUS_CFG_BURST_32;
	else {
		device_printf(dev, "unsupported burst size\n");
		goto fail;
	}
	/* Reset the SBus interface only. */
	(void)GEM_BANK2_READ_4(sc, GEM_SBUS_BIF_RESET);
	DELAY(100);
	GEM_BANK2_WRITE_4(sc, GEM_SBUS_CONFIG, val);

	if (gem_attach(sc) != 0) {
		device_printf(dev, "could not be attached\n");
		goto fail;
	}

	if (bus_setup_intr(dev, sc->sc_res[GEM_RES_INTR], INTR_TYPE_NET |
	    INTR_MPSAFE, NULL, gem_intr, sc, &sc->sc_ih) != 0) {
		device_printf(dev, "failed to set up interrupt\n");
		gem_detach(sc);
		goto fail;
	}
	return (0);

 fail:
	GEM_LOCK_DESTROY(sc);
	bus_release_resources(dev, gem_sbus_res_spec, sc->sc_res);
	return (ENXIO);
}