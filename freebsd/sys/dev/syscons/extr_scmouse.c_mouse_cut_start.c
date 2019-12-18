#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int status; int mouse_pos; int mouse_cut_start; int mouse_cut_end; int xsize; int /*<<< orphan*/  vtb; int /*<<< orphan*/  sc; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 int MOUSE_CUTTING ; 
 int MOUSE_VISIBLE ; 
 char* cut_buffer ; 
 int /*<<< orphan*/  mark_all (TYPE_1__*) ; 
 int rounddown (int,int) ; 
 int /*<<< orphan*/  sc_remove_all_cutmarkings (int /*<<< orphan*/ ) ; 
 char sc_vtb_getc (int /*<<< orphan*/ *,int) ; 
 int skip_spc_left (TYPE_1__*,int) ; 
 int skip_spc_right (TYPE_1__*,int) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void
mouse_cut_start(scr_stat *scp)
{
    int i;
    int s;

    if (scp->status & MOUSE_VISIBLE) {
	sc_remove_all_cutmarkings(scp->sc);
	if ((scp->mouse_pos == scp->mouse_cut_start) &&
	    (scp->mouse_pos == scp->mouse_cut_end)) {
	    cut_buffer[0] = '\0';
	    return;
	} else if (skip_spc_right(scp, scp->mouse_pos) >= scp->xsize) {
	    /* if the pointer is on trailing blank chars, mark towards eol */
	    i = skip_spc_left(scp, scp->mouse_pos) + 1;
	    s = spltty();
	    scp->mouse_cut_start =
	        rounddown(scp->mouse_pos, scp->xsize) + i;
	    scp->mouse_cut_end =
	        (scp->mouse_pos / scp->xsize + 1) * scp->xsize - 1;
	    splx(s);
	    cut_buffer[0] = '\r';
	} else {
	    s = spltty();
	    scp->mouse_cut_start = scp->mouse_pos;
	    scp->mouse_cut_end = scp->mouse_cut_start;
	    splx(s);
	    cut_buffer[0] = sc_vtb_getc(&scp->vtb, scp->mouse_cut_start);
	}
	cut_buffer[1] = '\0';
	scp->status |= MOUSE_CUTTING;
    	mark_all(scp);	/* this is probably overkill XXX */
    }
}