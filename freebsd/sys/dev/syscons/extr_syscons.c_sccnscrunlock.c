#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sc_cnstate {scalar_t__ kdb_locked; scalar_t__ mtx_locked; } ;
struct TYPE_3__ {int /*<<< orphan*/  video_mtx; } ;
typedef  TYPE_1__ sc_softc_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sccnscrunlock(sc_softc_t *sc, struct sc_cnstate *sp)
{
    if (sp->mtx_locked)
	mtx_unlock_spin(&sc->video_mtx);
    sp->mtx_locked = sp->kdb_locked = FALSE;
}