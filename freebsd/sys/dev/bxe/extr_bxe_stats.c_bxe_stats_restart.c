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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_VF (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_stats_comp (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_stats_start (struct bxe_softc*) ; 

__attribute__((used)) static void
bxe_stats_restart(struct bxe_softc *sc)
{
    /*
     * VFs travel through here as part of the statistics FSM, but no action
     * is required
     */
    if (IS_VF(sc)) {
        return;
    }

    bxe_stats_comp(sc);
    bxe_stats_start(sc);
}