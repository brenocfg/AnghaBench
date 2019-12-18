#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mouse_xpos; int xoff; int font_width; int mouse_ypos; int yoff; int font_size; int xpixel; int ypixel; int xsize; int ysize; int mouse_oldxpos; int mouse_oldypos; int status; int mouse_pos; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 scalar_t__ ISGRAPHSC (TYPE_1__*) ; 
 int MOUSE_CUTTING ; 
 int MOUSE_MOVED ; 
 int MOUSE_VISIBLE ; 
 int /*<<< orphan*/  mouse_cut (TYPE_1__*) ; 

__attribute__((used)) static void
set_mouse_pos(scr_stat *scp)
{
    if (scp->mouse_xpos < scp->xoff*scp->font_width)
	scp->mouse_xpos = scp->xoff*scp->font_width;
    if (scp->mouse_ypos < scp->yoff*scp->font_size)
	scp->mouse_ypos = scp->yoff*scp->font_size;
    if (ISGRAPHSC(scp)) {
        if (scp->mouse_xpos > scp->xpixel-1)
	    scp->mouse_xpos = scp->xpixel-1;
        if (scp->mouse_ypos > scp->ypixel-1)
	    scp->mouse_ypos = scp->ypixel-1;
	return;
    } else {
	if (scp->mouse_xpos > (scp->xsize + scp->xoff)*scp->font_width - 1)
	    scp->mouse_xpos = (scp->xsize + scp->xoff)*scp->font_width - 1;
	if (scp->mouse_ypos > (scp->ysize + scp->yoff)*scp->font_size - 1)
	    scp->mouse_ypos = (scp->ysize + scp->yoff)*scp->font_size - 1;
    }

    if ((scp->mouse_xpos != scp->mouse_oldxpos || scp->mouse_ypos != scp->mouse_oldypos)
	&& (scp->font_size != 0 && scp->font_width != 0)) {
	scp->status |= MOUSE_MOVED;
    	scp->mouse_pos =
	    (scp->mouse_ypos/scp->font_size - scp->yoff)*scp->xsize 
		+ scp->mouse_xpos/scp->font_width - scp->xoff;
#ifndef SC_NO_CUTPASTE
	if ((scp->status & MOUSE_VISIBLE) && (scp->status & MOUSE_CUTTING))
	    mouse_cut(scp);
#endif
    }
}