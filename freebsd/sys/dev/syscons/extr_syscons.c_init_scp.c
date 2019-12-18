#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int vi_flags; int vi_width; int vi_height; int vi_cwidth; int vi_cheight; } ;
typedef  TYPE_2__ video_info_t ;
struct TYPE_10__ {int /*<<< orphan*/  mode; } ;
struct TYPE_12__ {int index; int status; int xpixel; int ypixel; int xsize; int ysize; int font_size; int font_width; int start; int border; int mouse_cut_start; int mouse_cut_end; scalar_t__ history_size; scalar_t__ history_pos; int /*<<< orphan*/ * history; TYPE_1__ smode; int /*<<< orphan*/ * proc; scalar_t__ pid; int /*<<< orphan*/  bell_duration; int /*<<< orphan*/  bell_pitch; int /*<<< orphan*/  kbd_mode; int /*<<< orphan*/ * mouse_proc; scalar_t__ mouse_pid; scalar_t__ mouse_signal; int /*<<< orphan*/  dflt_curs_attr; int /*<<< orphan*/  base_curs_attr; int /*<<< orphan*/ * rndr; int /*<<< orphan*/ * ts; int /*<<< orphan*/ * tsw; scalar_t__ end; scalar_t__ ypos; scalar_t__ xpos; scalar_t__ yoff; scalar_t__ xoff; int /*<<< orphan*/  scr; int /*<<< orphan*/  vtb; int /*<<< orphan*/ * font; int /*<<< orphan*/  mode; TYPE_4__* sc; } ;
typedef  TYPE_3__ scr_stat ;
struct TYPE_13__ {int /*<<< orphan*/  curs_attr; int /*<<< orphan*/ * font_14; int /*<<< orphan*/ * font_16; int /*<<< orphan*/ * font_8; int /*<<< orphan*/  adp; int /*<<< orphan*/  initial_mode; } ;
typedef  TYPE_4__ sc_softc_t ;
struct TYPE_14__ {int shift_state; int /*<<< orphan*/  bell_pitch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BELL_DURATION ; 
 int CURSOR_ENABLED ; 
 int /*<<< orphan*/  FALSE ; 
 int GRAPHICS_MODE ; 
 int /*<<< orphan*/  K_XLATE ; 
 int MOUSE_HIDDEN ; 
 int NLKED ; 
 int SC_NORM_ATTR ; 
 int /*<<< orphan*/  VTB_FRAMEBUFFER ; 
 int /*<<< orphan*/  VTB_MEMORY ; 
 int /*<<< orphan*/  VT_AUTO ; 
 int V_INFO_GRAPHICS ; 
 TYPE_9__ bios_value ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sc_vtb_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vidd_get_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
init_scp(sc_softc_t *sc, int vty, scr_stat *scp)
{
    video_info_t info;

    bzero(scp, sizeof(*scp));

    scp->index = vty;
    scp->sc = sc;
    scp->status = 0;
    scp->mode = sc->initial_mode;
    vidd_get_info(sc->adp, scp->mode, &info);
    if (info.vi_flags & V_INFO_GRAPHICS) {
	scp->status |= GRAPHICS_MODE;
	scp->xpixel = info.vi_width;
	scp->ypixel = info.vi_height;
	scp->xsize = info.vi_width/info.vi_cwidth;
	scp->ysize = info.vi_height/info.vi_cheight;
	scp->font_size = 0;
	scp->font = NULL;
    } else {
	scp->xsize = info.vi_width;
	scp->ysize = info.vi_height;
	scp->xpixel = scp->xsize*info.vi_cwidth;
	scp->ypixel = scp->ysize*info.vi_cheight;
    }

    scp->font_size = info.vi_cheight;
    scp->font_width = info.vi_cwidth;
#ifndef SC_NO_FONT_LOADING
    if (info.vi_cheight < 14)
	scp->font = sc->font_8;
    else if (info.vi_cheight >= 16)
	scp->font = sc->font_16;
    else
	scp->font = sc->font_14;
#else
    scp->font = NULL;
#endif

    sc_vtb_init(&scp->vtb, VTB_MEMORY, 0, 0, NULL, FALSE);
#ifndef __sparc64__
    sc_vtb_init(&scp->scr, VTB_FRAMEBUFFER, 0, 0, NULL, FALSE);
#endif
    scp->xoff = scp->yoff = 0;
    scp->xpos = scp->ypos = 0;
    scp->start = scp->xsize * scp->ysize - 1;
    scp->end = 0;
    scp->tsw = NULL;
    scp->ts = NULL;
    scp->rndr = NULL;
    scp->border = (SC_NORM_ATTR >> 4) & 0x0f;
    scp->base_curs_attr = scp->dflt_curs_attr = sc->curs_attr;
    scp->mouse_cut_start = scp->xsize*scp->ysize;
    scp->mouse_cut_end = -1;
    scp->mouse_signal = 0;
    scp->mouse_pid = 0;
    scp->mouse_proc = NULL;
    scp->kbd_mode = K_XLATE;
    scp->bell_pitch = bios_value.bell_pitch;
    scp->bell_duration = BELL_DURATION;
    scp->status |= (bios_value.shift_state & NLKED);
    scp->status |= CURSOR_ENABLED | MOUSE_HIDDEN;
    scp->pid = 0;
    scp->proc = NULL;
    scp->smode.mode = VT_AUTO;
    scp->history = NULL;
    scp->history_pos = 0;
    scp->history_size = 0;
}