#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int xsize; int mouse_cut_start; int mouse_cut_end; int /*<<< orphan*/  vtb; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  IS_BLANK_CHAR (char) ; 
 scalar_t__ IS_SPACE_CHAR (char) ; 
 char* cut_buffer ; 
 int /*<<< orphan*/  mark_for_update (TYPE_1__*,int) ; 
 char sc_vtb_getc (int /*<<< orphan*/ *,int) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void
mouse_do_cut(scr_stat *scp, int from, int to)
{
    int blank;
    int i;
    int leadspaces;
    int p;
    int s;

    for (p = from, i = blank = leadspaces = 0; p <= to; ++p) {
	cut_buffer[i] = sc_vtb_getc(&scp->vtb, p);
	/* Be prepared that sc_vtb_getc() can return '\0' */
	if (cut_buffer[i] == '\0')
	    cut_buffer[i] = ' ';
#ifdef SC_CUT_SPACES2TABS
	if (leadspaces != -1) {
	    if (IS_SPACE_CHAR(cut_buffer[i])) {
		leadspaces++;
		/* Check that we are at tabstop position */
		if ((p % scp->xsize) % 8 == 7) {
		    i -= leadspaces - 1;
		    cut_buffer[i] = '\t';
		    leadspaces = 0;
		}
	    } else {
		leadspaces = -1;
	    }
	}
#endif /* SC_CUT_SPACES2TABS */
	/* remember the position of the last non-space char */
	if (!IS_BLANK_CHAR(cut_buffer[i]))
	    blank = i + 1;	/* the first space after the last non-space */
	++i;
	/* trim trailing blank when crossing lines */
	if ((p % scp->xsize) == (scp->xsize - 1)) {
	    cut_buffer[blank++] = '\r';
	    i = blank;
	    leadspaces = 0;
	}
    }
    cut_buffer[i] = '\0';

    /* remove the current marking */
    s = spltty();
    if (scp->mouse_cut_start <= scp->mouse_cut_end) {
	mark_for_update(scp, scp->mouse_cut_start);
	mark_for_update(scp, scp->mouse_cut_end);
    } else if (scp->mouse_cut_end >= 0) {
	mark_for_update(scp, scp->mouse_cut_end);
	mark_for_update(scp, scp->mouse_cut_start);
    }

    /* mark the new region */
    scp->mouse_cut_start = from;
    scp->mouse_cut_end = to;
    mark_for_update(scp, from);
    mark_for_update(scp, to);
    splx(s);
}