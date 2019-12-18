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
struct TYPE_2__ {scalar_t__ pmf; } ;
struct bxe_softc {scalar_t__ func_stx; TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ IS_VF (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_func_stats_init (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_hw_stats_post (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_port_stats_init (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_storm_stats_post (struct bxe_softc*) ; 

__attribute__((used)) static void
bxe_stats_start(struct bxe_softc *sc)
{
    /*
     * VFs travel through here as part of the statistics FSM, but no action
     * is required
     */
    if (IS_VF(sc)) {
        return;
    }

    if (sc->port.pmf) {
        bxe_port_stats_init(sc);
    }

    else if (sc->func_stx) {
        bxe_func_stats_init(sc);
    }

    bxe_hw_stats_post(sc);
    bxe_storm_stats_post(sc);
}