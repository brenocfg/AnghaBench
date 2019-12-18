#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int status; } ;
typedef  TYPE_1__ scr_stat ;
struct TYPE_7__ {int vtys; int /*<<< orphan*/ * dev; } ;
typedef  TYPE_2__ sc_softc_t ;

/* Variables and functions */
 int MOUSE_VISIBLE ; 
 TYPE_1__* SC_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_all (TYPE_1__*) ; 

void
sc_remove_all_mouse(sc_softc_t *sc)
{
    scr_stat *scp;
    int i;

    for (i = 0; i < sc->vtys; ++i) {
	scp = SC_STAT(sc->dev[i]);
	if (scp == NULL)
	    continue;
	if (scp->status & MOUSE_VISIBLE) {
	    scp->status &= ~MOUSE_VISIBLE;
	    mark_all(scp);
	}
    }
}