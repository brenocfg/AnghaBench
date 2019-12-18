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
struct TYPE_10__ {int status; int font_size; TYPE_2__* sc; } ;
typedef  TYPE_3__ scr_stat ;
struct TYPE_9__ {int fonts_loaded; int /*<<< orphan*/  font_14; int /*<<< orphan*/  font_16; int /*<<< orphan*/  font_8; TYPE_1__* adp; } ;
struct TYPE_8__ {int /*<<< orphan*/  va_flags; } ;

/* Variables and functions */
 int FONT_14 ; 
 int FONT_16 ; 
 int FONT_8 ; 
 int GRAPHICS_MODE ; 
 scalar_t__ ISFONTAVAIL (int /*<<< orphan*/ ) ; 
 int PIXEL_MODE ; 
 int /*<<< orphan*/  mark_all (TYPE_3__*) ; 
 int /*<<< orphan*/  sc_load_font (TYPE_3__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sc_show_font (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_font(scr_stat *scp)
{
#ifndef SC_NO_FONT_LOADING
    /* load appropriate font */
    if (!(scp->status & GRAPHICS_MODE)) {
	if (!(scp->status & PIXEL_MODE) && ISFONTAVAIL(scp->sc->adp->va_flags)) {
	    if (scp->font_size < 14) {
		if (scp->sc->fonts_loaded & FONT_8)
		    sc_load_font(scp, 0, 8, 8, scp->sc->font_8, 0, 256);
	    } else if (scp->font_size >= 16) {
		if (scp->sc->fonts_loaded & FONT_16)
		    sc_load_font(scp, 0, 16, 8, scp->sc->font_16, 0, 256);
	    } else {
		if (scp->sc->fonts_loaded & FONT_14)
		    sc_load_font(scp, 0, 14, 8, scp->sc->font_14, 0, 256);
	    }
	    /*
	     * FONT KLUDGE:
	     * This is an interim kludge to display correct font.
	     * Always use the font page #0 on the video plane 2.
	     * Somehow we cannot show the font in other font pages on
	     * some video cards... XXX
	     */ 
	    sc_show_font(scp, 0);
	}
	mark_all(scp);
    }
#endif /* !SC_NO_FONT_LOADING */
}