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
struct gem_softc {scalar_t__ sc_variant; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  GEM_BANK1_BARRIER (struct gem_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GEM_BANK1_BITWAIT (struct gem_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BANK1_WRITE_4 (struct gem_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GEM_BANK2_BARRIER (struct gem_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GEM_BANK2_BITWAIT (struct gem_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BANK2_WRITE_4 (struct gem_softc*,int /*<<< orphan*/ ,int) ; 
 int GEM_ERI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  GEM_MAC_RXRESET ; 
 int /*<<< orphan*/  GEM_RESET ; 
 int GEM_RESET_CLSZ_SHFT ; 
 int GEM_RESET_RX ; 
 int /*<<< orphan*/  GEM_RX_CONFIG ; 
 int GEM_RX_CONFIG_RXDMA_EN ; 
 scalar_t__ GEM_SUN_ERI ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gem_disable_rx (struct gem_softc*) ; 

__attribute__((used)) static int
gem_reset_rx(struct gem_softc *sc)
{

	/*
	 * Resetting while DMA is in progress can cause a bus hang, so we
	 * disable DMA first.
	 */
	(void)gem_disable_rx(sc);
	GEM_BANK1_WRITE_4(sc, GEM_RX_CONFIG, 0);
	GEM_BANK1_BARRIER(sc, GEM_RX_CONFIG, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	if (!GEM_BANK1_BITWAIT(sc, GEM_RX_CONFIG, GEM_RX_CONFIG_RXDMA_EN, 0))
		device_printf(sc->sc_dev, "cannot disable RX DMA\n");

	/* Wait 5ms extra. */
	DELAY(5000);

	/* Reset the ERX. */
	GEM_BANK2_WRITE_4(sc, GEM_RESET, GEM_RESET_RX |
	    (sc->sc_variant == GEM_SUN_ERI ? GEM_ERI_CACHE_LINE_SIZE <<
	    GEM_RESET_CLSZ_SHFT : 0));
	GEM_BANK2_BARRIER(sc, GEM_RESET, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	if (!GEM_BANK2_BITWAIT(sc, GEM_RESET, GEM_RESET_RX, 0)) {
		device_printf(sc->sc_dev, "cannot reset receiver\n");
		return (1);
	}

	/* Finally, reset RX MAC. */
	GEM_BANK1_WRITE_4(sc, GEM_MAC_RXRESET, 1);
	GEM_BANK1_BARRIER(sc, GEM_MAC_RXRESET, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	if (!GEM_BANK1_BITWAIT(sc, GEM_MAC_RXRESET, 1, 0)) {
		device_printf(sc->sc_dev, "cannot reset RX MAC\n");
		return (1);
	}

	return (0);
}