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
struct TYPE_2__ {scalar_t__ link_up; } ;
struct bxe_softc {int /*<<< orphan*/  cmng; TYPE_1__ link_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMNG_FNS_MINMAX ; 
 int /*<<< orphan*/  SC_PORT (struct bxe_softc*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bxe_cmng_fns_init (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storm_memset_cmng (struct bxe_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_config_mf_bw(struct bxe_softc *sc)
{
    if (sc->link_vars.link_up) {
        bxe_cmng_fns_init(sc, TRUE, CMNG_FNS_MINMAX);
        // XXX bxe_link_sync_notify(sc);
    }

    storm_memset_cmng(sc, &sc->cmng, SC_PORT(sc));
}