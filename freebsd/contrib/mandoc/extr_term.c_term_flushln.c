#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct termp {int flags; scalar_t__ viscol; size_t minbl; scalar_t__ maxrmargin; size_t (* width ) (struct termp*,char) ;size_t col; size_t trailspace; TYPE_1__* tcol; } ;
struct TYPE_2__ {scalar_t__ offset; size_t col; size_t rmargin; size_t lastcol; int* buf; } ;

/* Variables and functions */
#define  ASCII_BREAK 128 
 size_t SIZE_MAX ; 
 int TERMP_BACKAFTER ; 
 int TERMP_BACKBEFORE ; 
 int TERMP_BRIND ; 
 int TERMP_BRNEVER ; 
 int TERMP_BRTRSP ; 
 int TERMP_CENTER ; 
 int TERMP_HANG ; 
 int TERMP_MULTICOL ; 
 int TERMP_NOBREAK ; 
 int TERMP_NOPAD ; 
 int TERMP_RIGHT ; 
 int /*<<< orphan*/  endline (struct termp*) ; 
 size_t stub1 (struct termp*,char) ; 
 int /*<<< orphan*/  term_field (struct termp*,size_t,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  term_fill (struct termp*,size_t*,size_t*,size_t) ; 
 size_t term_len (struct termp*,size_t) ; 
 size_t term_tab_next (size_t) ; 

void
term_flushln(struct termp *p)
{
	size_t	 vbl;      /* Number of blanks to prepend to the output. */
	size_t	 vbr;      /* Actual visual position of the end of field. */
	size_t	 vfield;   /* Desired visual field width. */
	size_t	 vtarget;  /* Desired visual position of the right margin. */
	size_t	 ic;       /* Character position in the input buffer. */
	size_t	 nbr;      /* Number of characters to print in this field. */

	/*
	 * Normally, start writing at the left margin, but with the
	 * NOPAD flag, start writing at the current position instead.
	 */

	vbl = (p->flags & TERMP_NOPAD) || p->tcol->offset < p->viscol ?
	    0 : p->tcol->offset - p->viscol;
	if (p->minbl && vbl < p->minbl)
		vbl = p->minbl;

	if ((p->flags & TERMP_MULTICOL) == 0)
		p->tcol->col = 0;

	/* Loop over output lines. */

	for (;;) {
		vfield = p->tcol->rmargin > p->viscol + vbl ?
		    p->tcol->rmargin - p->viscol - vbl : 0;

		/*
		 * Normally, break the line at the the right margin
		 * of the field, but with the NOBREAK flag, only
		 * break it at the max right margin of the screen,
		 * and with the BRNEVER flag, never break it at all.
		 */

		vtarget = p->flags & TERMP_BRNEVER ? SIZE_MAX :
		    (p->flags & TERMP_NOBREAK) == 0 ? vfield :
		    p->maxrmargin > p->viscol + vbl ?
		    p->maxrmargin - p->viscol - vbl : 0;

		/*
		 * Figure out how much text will fit in the field.
		 * If there is whitespace only, print nothing.
		 */

		term_fill(p, &nbr, &vbr, vtarget);
		if (nbr == 0)
			break;

		/*
		 * With the CENTER or RIGHT flag, increase the indentation
		 * to center the text between the left and right margins
		 * or to adjust it to the right margin, respectively.
		 */

		if (vbr < vtarget) {
			if (p->flags & TERMP_CENTER)
				vbl += (vtarget - vbr) / 2;
			else if (p->flags & TERMP_RIGHT)
				vbl += vtarget - vbr;
		}

		/* Finally, print the field content. */

		term_field(p, vbl, nbr, vbr, vtarget);

		/*
		 * If there is no text left in the field, exit the loop.
		 * If the BRTRSP flag is set, consider trailing
		 * whitespace significant when deciding whether
		 * the field fits or not.
		 */

		for (ic = p->tcol->col; ic < p->tcol->lastcol; ic++) {
			switch (p->tcol->buf[ic]) {
			case '\t':
				if (p->flags & TERMP_BRTRSP)
					vbr = term_tab_next(vbr);
				continue;
			case ' ':
				if (p->flags & TERMP_BRTRSP)
					vbr += (*p->width)(p, ' ');
				continue;
			case '\n':
			case ASCII_BREAK:
				continue;
			default:
				break;
			}
			break;
		}
		if (ic == p->tcol->lastcol)
			break;

		/*
		 * At the location of an automtic line break, input
		 * space characters are consumed by the line break.
		 */

		while (p->tcol->col < p->tcol->lastcol &&
		    p->tcol->buf[p->tcol->col] == ' ')
			p->tcol->col++;

		/*
		 * In multi-column mode, leave the rest of the text
		 * in the buffer to be handled by a subsequent
		 * invocation, such that the other columns of the
		 * table can be handled first.
		 * In single-column mode, simply break the line.
		 */

		if (p->flags & TERMP_MULTICOL)
			return;

		endline(p);
		p->viscol = 0;

		/*
		 * Normally, start the next line at the same indentation
		 * as this one, but with the BRIND flag, start it at the
		 * right margin instead.  This is used together with
		 * NOBREAK for the tags in various kinds of tagged lists.
		 */

		vbl = p->flags & TERMP_BRIND ?
		    p->tcol->rmargin : p->tcol->offset;
	}

	/* Reset output state in preparation for the next field. */

	p->col = p->tcol->col = p->tcol->lastcol = 0;
	p->minbl = p->trailspace;
	p->flags &= ~(TERMP_BACKAFTER | TERMP_BACKBEFORE | TERMP_NOPAD);

	if (p->flags & TERMP_MULTICOL)
		return;

	/*
	 * The HANG flag means that the next field
	 * always follows on the same line.
	 * The NOBREAK flag means that the next field
	 * follows on the same line unless the field was overrun.
	 * Normally, break the line at the end of each field.
	 */

	if ((p->flags & TERMP_HANG) == 0 &&
	    ((p->flags & TERMP_NOBREAK) == 0 ||
	     vbr + term_len(p, p->trailspace) > vfield))
		endline(p);
}