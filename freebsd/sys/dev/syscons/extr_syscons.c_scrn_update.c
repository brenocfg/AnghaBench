#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_16__ ;

/* Type definitions */
struct TYPE_19__ {int flags; } ;
struct TYPE_21__ {int status; int mouse_pos; int xsize; int start; int end; int cursor_pos; int cursor_oldpos; int ysize; int mouse_cut_end; int mouse_cut_start; TYPE_16__* sc; TYPE_2__* rndr; TYPE_1__ curs_attr; } ;
typedef  TYPE_3__ scr_stat ;
struct TYPE_20__ {int /*<<< orphan*/  (* blink_cursor ) (TYPE_3__*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* draw ) (TYPE_3__*,int,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_18__ {int flags; } ;

/* Variables and functions */
 int CONS_BLINK_CURSOR ; 
 int CURSOR_ENABLED ; 
 int /*<<< orphan*/  FALSE ; 
 int MOUSE_HIDDEN ; 
 int MOUSE_MOVED ; 
 int MOUSE_VISIBLE ; 
 int SC_MOUSE_ENABLED ; 
 int /*<<< orphan*/  SC_VIDEO_LOCK (TYPE_16__*) ; 
 int /*<<< orphan*/  SC_VIDEO_UNLOCK (TYPE_16__*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ and_region (int*,int*,int,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sc_draw_cursor_image (TYPE_3__*) ; 
 int /*<<< orphan*/  sc_draw_mouse_image (TYPE_3__*) ; 
 int /*<<< orphan*/  sc_inside_cutmark (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sc_remove_cursor_image (TYPE_3__*) ; 
 int /*<<< orphan*/  sc_remove_mouse_image (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
scrn_update(scr_stat *scp, int show_cursor)
{
    int start;
    int end;
    int s;
    int e;

    /* assert(scp == scp->sc->cur_scp) */

    SC_VIDEO_LOCK(scp->sc);

#ifndef SC_NO_CUTPASTE
    /* remove the previous mouse pointer image if necessary */
    if (scp->status & MOUSE_VISIBLE) {
	s = scp->mouse_pos;
	e = scp->mouse_pos + scp->xsize + 1;
	if ((scp->status & (MOUSE_MOVED | MOUSE_HIDDEN))
	    || and_region(&s, &e, scp->start, scp->end)
	    || ((scp->status & CURSOR_ENABLED) && 
		(scp->cursor_pos != scp->cursor_oldpos) &&
		(and_region(&s, &e, scp->cursor_pos, scp->cursor_pos)
		 || and_region(&s, &e, scp->cursor_oldpos, scp->cursor_oldpos)))) {
	    sc_remove_mouse_image(scp);
	    if (scp->end >= scp->xsize*scp->ysize)
		scp->end = scp->xsize*scp->ysize - 1;
	}
    }
#endif /* !SC_NO_CUTPASTE */

#if 1
    /* debug: XXX */
    if (scp->end >= scp->xsize*scp->ysize) {
	printf("scrn_update(): scp->end %d > size_of_screen!!\n", scp->end);
	scp->end = scp->xsize*scp->ysize - 1;
    }
    if (scp->start < 0) {
	printf("scrn_update(): scp->start %d < 0\n", scp->start);
	scp->start = 0;
    }
#endif

    /* update screen image */
    if (scp->start <= scp->end)  {
	if (scp->mouse_cut_end >= 0) {
	    /* there is a marked region for cut & paste */
	    if (scp->mouse_cut_start <= scp->mouse_cut_end) {
		start = scp->mouse_cut_start;
		end = scp->mouse_cut_end;
	    } else {
		start = scp->mouse_cut_end;
		end = scp->mouse_cut_start - 1;
	    }
	    s = start;
	    e = end;
	    /* does the cut-mark region overlap with the update region? */
	    if (and_region(&s, &e, scp->start, scp->end)) {
		(*scp->rndr->draw)(scp, s, e - s + 1, TRUE);
		s = 0;
		e = start - 1;
		if (and_region(&s, &e, scp->start, scp->end))
		    (*scp->rndr->draw)(scp, s, e - s + 1, FALSE);
		s = end + 1;
		e = scp->xsize*scp->ysize - 1;
		if (and_region(&s, &e, scp->start, scp->end))
		    (*scp->rndr->draw)(scp, s, e - s + 1, FALSE);
	    } else {
		(*scp->rndr->draw)(scp, scp->start,
				   scp->end - scp->start + 1, FALSE);
	    }
	} else {
	    (*scp->rndr->draw)(scp, scp->start,
			       scp->end - scp->start + 1, FALSE);
	}
    }

    /* we are not to show the cursor and the mouse pointer... */
    if (!show_cursor) {
        scp->end = 0;
        scp->start = scp->xsize*scp->ysize - 1;
	SC_VIDEO_UNLOCK(scp->sc);
	return;
    }

    /* update cursor image */
    if (scp->status & CURSOR_ENABLED) {
	s = scp->start;
	e = scp->end;
        /* did cursor move since last time ? */
        if (scp->cursor_pos != scp->cursor_oldpos) {
            /* do we need to remove old cursor image ? */
            if (!and_region(&s, &e, scp->cursor_oldpos, scp->cursor_oldpos))
                sc_remove_cursor_image(scp);
            sc_draw_cursor_image(scp);
        } else {
            if (and_region(&s, &e, scp->cursor_pos, scp->cursor_pos))
		/* cursor didn't move, but has been overwritten */
		sc_draw_cursor_image(scp);
	    else if (scp->curs_attr.flags & CONS_BLINK_CURSOR)
		/* if it's a blinking cursor, update it */
		(*scp->rndr->blink_cursor)(scp, scp->cursor_pos,
					   sc_inside_cutmark(scp,
					       scp->cursor_pos));
        }
    }

#ifndef SC_NO_CUTPASTE
    /* update "pseudo" mouse pointer image */
    if (scp->sc->flags & SC_MOUSE_ENABLED) {
	if (!(scp->status & (MOUSE_VISIBLE | MOUSE_HIDDEN))) {
	    scp->status &= ~MOUSE_MOVED;
	    sc_draw_mouse_image(scp);
	}
    }
#endif /* SC_NO_CUTPASTE */

    scp->end = 0;
    scp->start = scp->xsize*scp->ysize - 1;

    SC_VIDEO_UNLOCK(scp->sc);
}