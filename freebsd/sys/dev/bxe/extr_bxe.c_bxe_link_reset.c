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
struct bxe_softc {int /*<<< orphan*/  link_vars; int /*<<< orphan*/  link_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGW (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  BXE_NOMCP (struct bxe_softc*) ; 
 int /*<<< orphan*/  CHIP_REV_IS_SLOW (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_acquire_phy_lock (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_release_phy_lock (struct bxe_softc*) ; 
 int /*<<< orphan*/  elink_lfa_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bxe_link_reset(struct bxe_softc *sc)
{
    if (!BXE_NOMCP(sc)) {
	bxe_acquire_phy_lock(sc);
        elink_lfa_reset(&sc->link_params, &sc->link_vars);
	bxe_release_phy_lock(sc);
    } else {
        if (!CHIP_REV_IS_SLOW(sc)) {
            BLOGW(sc, "Bootcode is missing - cannot reset link\n");
        }
    }
}