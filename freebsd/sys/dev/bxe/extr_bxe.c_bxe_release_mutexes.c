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
struct TYPE_2__ {int /*<<< orphan*/  phy_mtx; } ;
struct bxe_softc {int /*<<< orphan*/  mcast_mtx; int /*<<< orphan*/  stats_mtx; int /*<<< orphan*/  print_mtx; int /*<<< orphan*/  fwmb_mtx; TYPE_1__ port; int /*<<< orphan*/  dmae_mtx; int /*<<< orphan*/  sp_mtx; int /*<<< orphan*/  core_mtx; int /*<<< orphan*/  core_sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bxe_release_mutexes(struct bxe_softc *sc)
{
#ifdef BXE_CORE_LOCK_SX
    sx_destroy(&sc->core_sx);
#else
    if (mtx_initialized(&sc->core_mtx)) {
        mtx_destroy(&sc->core_mtx);
    }
#endif

    if (mtx_initialized(&sc->sp_mtx)) {
        mtx_destroy(&sc->sp_mtx);
    }

    if (mtx_initialized(&sc->dmae_mtx)) {
        mtx_destroy(&sc->dmae_mtx);
    }

    if (mtx_initialized(&sc->port.phy_mtx)) {
        mtx_destroy(&sc->port.phy_mtx);
    }

    if (mtx_initialized(&sc->fwmb_mtx)) {
        mtx_destroy(&sc->fwmb_mtx);
    }

    if (mtx_initialized(&sc->print_mtx)) {
        mtx_destroy(&sc->print_mtx);
    }

    if (mtx_initialized(&sc->stats_mtx)) {
        mtx_destroy(&sc->stats_mtx);
    }

    if (mtx_initialized(&sc->mcast_mtx)) {
        mtx_destroy(&sc->mcast_mtx);
    }
}