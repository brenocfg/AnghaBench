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
 int /*<<< orphan*/  GEM_BANK1_BITWAIT (struct gem_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BANK1_WRITE_4 (struct gem_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BANK2_BARRIER (struct gem_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GEM_BANK2_BITWAIT (struct gem_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BANK2_WRITE_4 (struct gem_softc*,int /*<<< orphan*/ ,int) ; 
 int GEM_ERI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  GEM_RESET ; 
 int GEM_RESET_CLSZ_SHFT ; 
 int GEM_RESET_TX ; 
 scalar_t__ GEM_SUN_ERI ; 
 int /*<<< orphan*/  GEM_TX_CONFIG ; 
 int /*<<< orphan*/  GEM_TX_CONFIG_TXDMA_EN ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gem_disable_tx (struct gem_softc*) ; 

__attribute__((used)) static int
gem_reset_tx(struct gem_softc *sc)
{

	/*
	 * Resetting while DMA is in progress can cause a bus hang, so we
	 * disable DMA first.
	 */
	(void)gem_disable_tx(sc);
	GEM_BANK1_WRITE_4(sc, GEM_TX_CONFIG, 0);
	GEM_BANK1_BARRIER(sc, GEM_TX_CONFIG, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	if (!GEM_BANK1_BITWAIT(sc, GEM_TX_CONFIG, GEM_TX_CONFIG_TXDMA_EN, 0))
		device_printf(sc->sc_dev, "cannot disable TX DMA\n");

	/* Wait 5ms extra. */
	DELAY(5000);

	/* Finally, reset the ETX. */
	GEM_BANK2_WRITE_4(sc, GEM_RESET, GEM_RESET_TX |
	    (sc->sc_variant == GEM_SUN_ERI ? GEM_ERI_CACHE_LINE_SIZE <<
	    GEM_RESET_CLSZ_SHFT : 0));
	GEM_BANK2_BARRIER(sc, GEM_RESET, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	if (!GEM_BANK2_BITWAIT(sc, GEM_RESET, GEM_RESET_TX, 0)) {
		device_printf(sc->sc_dev, "cannot reset transmitter\n");
		return (1);
	}
	return (0);
}