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
struct gem_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  GEM_BANK1_BARRIER (struct gem_softc*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ GEM_BANK1_BITWAIT (struct gem_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int GEM_BANK1_READ_4 (struct gem_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BANK1_WRITE_4 (struct gem_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GEM_MAC_TX_CONFIG ; 
 int GEM_MAC_TX_ENABLE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
gem_disable_tx(struct gem_softc *sc)
{

	GEM_BANK1_WRITE_4(sc, GEM_MAC_TX_CONFIG,
	    GEM_BANK1_READ_4(sc, GEM_MAC_TX_CONFIG) & ~GEM_MAC_TX_ENABLE);
	GEM_BANK1_BARRIER(sc, GEM_MAC_TX_CONFIG, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	if (GEM_BANK1_BITWAIT(sc, GEM_MAC_TX_CONFIG, GEM_MAC_TX_ENABLE, 0))
		return (1);
	device_printf(sc->sc_dev, "cannot disable TX MAC\n");
	return (0);
}