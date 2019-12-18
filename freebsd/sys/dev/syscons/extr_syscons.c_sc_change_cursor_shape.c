#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tty {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dflt_curs_attr; TYPE_2__* sc; } ;
typedef  TYPE_1__ scr_stat ;
struct TYPE_8__ {int first_vty; int vtys; int /*<<< orphan*/  curs_attr; int /*<<< orphan*/  dflt_curs_attr; } ;
typedef  TYPE_2__ sc_softc_t ;

/* Variables and functions */
 int CONS_DEFAULT_CURSOR ; 
 int CONS_LOCAL_CURSOR ; 
 int CONS_RESET_CURSOR ; 
 int CONS_SHAPEONLY_CURSOR ; 
 struct tty* SC_DEV (TYPE_2__*,int) ; 
 int /*<<< orphan*/  change_cursor_shape (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  sc_adjust_ca (int /*<<< orphan*/ *,int,int,int) ; 
 TYPE_1__* sc_get_stat (struct tty*) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

void
sc_change_cursor_shape(scr_stat *scp, int flags, int base, int height)
{
    sc_softc_t *sc;
    struct tty *tp;
    int s;
    int i;

    if (flags == -1)
	flags = CONS_SHAPEONLY_CURSOR;

    s = spltty();
    if (flags & CONS_LOCAL_CURSOR) {
	/* local (per vty) change */
	change_cursor_shape(scp, flags, base, height);
	splx(s);
	return;
    }

    /* global change */
    sc = scp->sc;
    if (flags & CONS_RESET_CURSOR)
	sc->curs_attr = sc->dflt_curs_attr;
    else if (flags & CONS_DEFAULT_CURSOR) {
	sc_adjust_ca(&sc->dflt_curs_attr, flags, base, height);
	sc->curs_attr = sc->dflt_curs_attr;
    } else
	sc_adjust_ca(&sc->curs_attr, flags, base, height);

    for (i = sc->first_vty; i < sc->first_vty + sc->vtys; ++i) {
	if ((tp = SC_DEV(sc, i)) == NULL)
	    continue;
	if ((scp = sc_get_stat(tp)) == NULL)
	    continue;
	scp->dflt_curs_attr = sc->curs_attr;
	change_cursor_shape(scp, CONS_RESET_CURSOR, -1, -1);
    }
    splx(s);
}