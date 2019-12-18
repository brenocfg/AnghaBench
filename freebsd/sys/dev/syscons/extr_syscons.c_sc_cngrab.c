#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct consdev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * grab_state; int /*<<< orphan*/  grab_level; } ;
typedef  TYPE_1__ sc_softc_t ;
struct TYPE_7__ {TYPE_1__* sc; } ;

/* Variables and functions */
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 TYPE_5__* sc_console ; 
 int /*<<< orphan*/  sccnkbdunlock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sccnopen (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sccnscrunlock (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sc_cngrab(struct consdev *cp)
{
    sc_softc_t *sc;
    int lev;

    sc = sc_console->sc;
    lev = atomic_fetchadd_int(&sc->grab_level, 1);
    if (lev >= 0 && lev < 2) {
	sccnopen(sc, &sc->grab_state[lev], 1 | 2);
	sccnscrunlock(sc, &sc->grab_state[lev]);
	sccnkbdunlock(sc, &sc->grab_state[lev]);
    }
}