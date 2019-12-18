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
typedef  int /*<<< orphan*/  scr_stat ;
struct TYPE_3__ {int vtys; int /*<<< orphan*/ * dev; } ;
typedef  TYPE_1__ sc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SC_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_remove_cutmarking (int /*<<< orphan*/ *) ; 

void
sc_remove_all_cutmarkings(sc_softc_t *sc)
{
    scr_stat *scp;
    int i;

    /* delete cut markings in all vtys */
    for (i = 0; i < sc->vtys; ++i) {
	scp = SC_STAT(sc->dev[i]);
	if (scp == NULL)
	    continue;
	sc_remove_cutmarking(scp);
    }
}