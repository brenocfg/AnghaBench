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
typedef  int uint8_t ;
struct TYPE_2__ {scalar_t__ pmf; } ;
struct bxe_softc {TYPE_1__ port; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  bxe_hw_stats_post (struct bxe_softc*) ; 
 scalar_t__ bxe_hw_stats_update (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_net_stats_update (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_port_stats_stop (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_stats_comp (struct bxe_softc*) ; 
 scalar_t__ bxe_storm_stats_update (struct bxe_softc*) ; 

__attribute__((used)) static void
bxe_stats_stop(struct bxe_softc *sc)
{
    uint8_t update = FALSE;

    bxe_stats_comp(sc);

    if (sc->port.pmf) {
        update = bxe_hw_stats_update(sc) == 0;
    }

    update |= bxe_storm_stats_update(sc) == 0;

    if (update) {
        bxe_net_stats_update(sc);

        if (sc->port.pmf) {
            bxe_port_stats_stop(sc);
        }

        bxe_hw_stats_post(sc);
        bxe_stats_comp(sc);
    }
}