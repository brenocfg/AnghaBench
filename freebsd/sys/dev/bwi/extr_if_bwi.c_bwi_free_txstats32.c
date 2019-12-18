#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bwi_softc {TYPE_1__* sc_txstats; } ;
struct TYPE_2__ {int /*<<< orphan*/  stats_ctrl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  bwi_reset_rx_ring32 (struct bwi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwi_free_txstats32(struct bwi_softc *sc)
{
	bwi_reset_rx_ring32(sc, sc->sc_txstats->stats_ctrl_base);
}