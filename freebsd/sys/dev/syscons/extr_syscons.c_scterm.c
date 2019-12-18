#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * ts; TYPE_1__* tsw; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_10__ {int flags; int keyboard; int adapter; int /*<<< orphan*/ * font_16; int /*<<< orphan*/ * font_14; int /*<<< orphan*/ * font_8; int /*<<< orphan*/ * tty; int /*<<< orphan*/ * dev; int /*<<< orphan*/  video_mtx; int /*<<< orphan*/  adp; int /*<<< orphan*/  kbd; } ;
typedef  TYPE_3__ sc_softc_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* te_term ) (TYPE_2__*,int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int SC_KERNEL_CONSOLE ; 
 int SC_SPLASH_SCRN ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_release (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 TYPE_3__* sc_get_softc (int,int) ; 
 TYPE_2__* sc_get_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splash_term (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vid_release (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vidd_set_hw_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scterm(int unit, int flags)
{
    sc_softc_t *sc;
    scr_stat *scp;

    sc = sc_get_softc(unit, flags & SC_KERNEL_CONSOLE);
    if (sc == NULL)
	return;			/* shouldn't happen */

#ifdef DEV_SPLASH
    /* this console is no longer available for the splash screen */
    if (sc->flags & SC_SPLASH_SCRN) {
	splash_term(sc->adp);
	sc->flags &= ~SC_SPLASH_SCRN;
    }
#endif

#if 0 /* XXX */
    /* move the hardware cursor to the upper-left corner */
    vidd_set_hw_cursor(sc->adp, 0, 0);
#endif

    /* release the keyboard and the video card */
    if (sc->keyboard >= 0)
	kbd_release(sc->kbd, &sc->keyboard);
    if (sc->adapter >= 0)
	vid_release(sc->adp, &sc->adapter);

    /* stop the terminal emulator, if any */
    scp = sc_get_stat(sc->dev[0]);
    if (scp->tsw)
	(*scp->tsw->te_term)(scp, &scp->ts);
    mtx_destroy(&sc->video_mtx);

    /* clear the structure */
    if (!(flags & SC_KERNEL_CONSOLE)) {
	free(scp->ts, M_DEVBUF);
	/* XXX: We need delete_dev() for this */
	free(sc->dev, M_DEVBUF);
#if 0
	/* XXX: We need a ttyunregister for this */
	free(sc->tty, M_DEVBUF);
#endif
#ifndef SC_NO_FONT_LOADING
	free(sc->font_8, M_DEVBUF);
	free(sc->font_14, M_DEVBUF);
	free(sc->font_16, M_DEVBUF);
#endif
	/* XXX vtb, history */
    }
    bzero(sc, sizeof(*sc));
    sc->keyboard = -1;
    sc->adapter = -1;
}