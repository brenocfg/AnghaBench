#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_info_t ;
struct TYPE_13__ {int /*<<< orphan*/  border; TYPE_2__* sc; int /*<<< orphan*/  ysize; int /*<<< orphan*/  xsize; int /*<<< orphan*/  scr; TYPE_1__* rndr; int /*<<< orphan*/  mode; } ;
typedef  TYPE_3__ scr_stat ;
struct TYPE_14__ {scalar_t__ va_window; } ;
struct TYPE_12__ {TYPE_4__* adp; TYPE_3__* cur_scp; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* init ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  VTB_FRAMEBUFFER ; 
 int /*<<< orphan*/  sc_set_border (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_set_cursor_image (TYPE_3__*) ; 
 int /*<<< orphan*/  sc_vtb_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  update_font (TYPE_3__*) ; 
 scalar_t__ vidd_get_info (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vidd_set_mode (TYPE_4__*,int /*<<< orphan*/ ) ; 

int
set_mode(scr_stat *scp)
{
    video_info_t info;

    /* reject unsupported mode */
    if (vidd_get_info(scp->sc->adp, scp->mode, &info))
	return 1;

    /* if this vty is not currently showing, do nothing */
    if (scp != scp->sc->cur_scp)
	return 0;

    /* setup video hardware for the given mode */
    vidd_set_mode(scp->sc->adp, scp->mode);
    scp->rndr->init(scp);
#ifndef __sparc64__
    sc_vtb_init(&scp->scr, VTB_FRAMEBUFFER, scp->xsize, scp->ysize,
		(void *)scp->sc->adp->va_window, FALSE);
#endif

    update_font(scp);

    sc_set_border(scp, scp->border);
    sc_set_cursor_image(scp);

    return 0;
}