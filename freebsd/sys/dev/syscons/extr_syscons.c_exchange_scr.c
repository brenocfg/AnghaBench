#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ kbd_mode; scalar_t__ mode; int /*<<< orphan*/  status; int /*<<< orphan*/  border; int /*<<< orphan*/  ypos; int /*<<< orphan*/  xpos; int /*<<< orphan*/  ysize; int /*<<< orphan*/  xsize; int /*<<< orphan*/  scr; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_18__ {scalar_t__ kbd_open_level; int /*<<< orphan*/  kbd; TYPE_2__* old_scp; int /*<<< orphan*/  palette; TYPE_4__* adp; int /*<<< orphan*/  palette2; TYPE_2__* new_scp; TYPE_2__* cur_scp; } ;
typedef  TYPE_3__ sc_softc_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_16__ {scalar_t__ vi_mem_model; } ;
struct TYPE_19__ {TYPE_1__ va_info; scalar_t__ va_window; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ISGRAPHSC (TYPE_2__*) ; 
 scalar_t__ ISUNKNOWNSC (TYPE_2__*) ; 
 int /*<<< orphan*/  KDSKBMODE ; 
 scalar_t__ K_XLATE ; 
 int /*<<< orphan*/  LOCK_MASK ; 
 int /*<<< orphan*/  MOUSE_HIDDEN ; 
 int /*<<< orphan*/  VTB_FRAMEBUFFER ; 
 scalar_t__ V_INFO_MM_DIRECT ; 
 int /*<<< orphan*/  kbdd_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_all (TYPE_2__*) ; 
 int /*<<< orphan*/  save_kbd_state (TYPE_2__*) ; 
 int /*<<< orphan*/  sc_move_cursor (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_remove_cursor_image (TYPE_2__*) ; 
 int /*<<< orphan*/  sc_set_border (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_set_cursor_image (TYPE_2__*) ; 
 int /*<<< orphan*/  sc_vtb_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mode (TYPE_2__*) ; 
 int /*<<< orphan*/  update_kbd_state (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vidd_load_palette (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
exchange_scr(sc_softc_t *sc)
{
    scr_stat *scp;

    /* save the current state of video and keyboard */
    sc_move_cursor(sc->old_scp, sc->old_scp->xpos, sc->old_scp->ypos);
    if (!ISGRAPHSC(sc->old_scp))
	sc_remove_cursor_image(sc->old_scp);
    if (sc->old_scp->kbd_mode == K_XLATE)
	save_kbd_state(sc->old_scp);

    /* set up the video for the new screen */
    scp = sc->cur_scp = sc->new_scp;
    if (sc->old_scp->mode != scp->mode || ISUNKNOWNSC(sc->old_scp))
	set_mode(scp);
#ifndef __sparc64__
    else
	sc_vtb_init(&scp->scr, VTB_FRAMEBUFFER, scp->xsize, scp->ysize,
		    (void *)sc->adp->va_window, FALSE);
#endif
    scp->status |= MOUSE_HIDDEN;
    sc_move_cursor(scp, scp->xpos, scp->ypos);
    if (!ISGRAPHSC(scp))
	sc_set_cursor_image(scp);
#ifndef SC_NO_PALETTE_LOADING
    if (ISGRAPHSC(sc->old_scp)) {
#ifdef SC_PIXEL_MODE
	if (sc->adp->va_info.vi_mem_model == V_INFO_MM_DIRECT)
	    vidd_load_palette(sc->adp, sc->palette2);
	else
#endif
	vidd_load_palette(sc->adp, sc->palette);
    }
#endif
    sc_set_border(scp, scp->border);

    /* set up the keyboard for the new screen */
    if (sc->kbd_open_level == 0 && sc->old_scp->kbd_mode != scp->kbd_mode)
	(void)kbdd_ioctl(sc->kbd, KDSKBMODE, (caddr_t)&scp->kbd_mode);
    update_kbd_state(scp, scp->status, LOCK_MASK);

    mark_all(scp);
}