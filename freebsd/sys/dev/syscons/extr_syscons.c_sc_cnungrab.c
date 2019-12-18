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
struct TYPE_6__ {int /*<<< orphan*/  grab_level; int /*<<< orphan*/ * grab_state; } ;
typedef  TYPE_1__ sc_softc_t ;
struct TYPE_7__ {TYPE_1__* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 TYPE_5__* sc_console ; 
 int /*<<< orphan*/  sccnclose (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sccnkbdlock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sccnscrlock (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sc_cnungrab(struct consdev *cp)
{
    sc_softc_t *sc;
    int lev;

    sc = sc_console->sc;
    lev = atomic_load_acq_int(&sc->grab_level) - 1;
    if (lev >= 0 && lev < 2) {
	sccnkbdlock(sc, &sc->grab_state[lev]);
	sccnscrlock(sc, &sc->grab_state[lev]);
	sccnclose(sc, &sc->grab_state[lev]);
    }
    atomic_add_int(&sc->grab_level, -1);
}