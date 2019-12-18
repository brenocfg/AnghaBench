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
struct termp {size_t (* width ) (struct termp*,char) ;size_t viscol; TYPE_1__* tcol; int /*<<< orphan*/  (* letter ) (struct termp*,int) ;int /*<<< orphan*/  (* advance ) (struct termp*,size_t) ;} ;
struct TYPE_2__ {size_t col; int* buf; } ;

/* Variables and functions */
#define  ASCII_BREAK 129 
#define  ASCII_NBRSP 128 
 size_t stub1 (struct termp*,char) ; 
 int /*<<< orphan*/  stub2 (struct termp*,size_t) ; 
 int /*<<< orphan*/  stub3 (struct termp*,int) ; 
 size_t stub4 (struct termp*,char) ; 
 size_t stub5 (struct termp*,char) ; 
 size_t term_tab_next (size_t) ; 

__attribute__((used)) static void
term_field(struct termp *p, size_t vbl, size_t nbr, size_t vbr, size_t vtarget)
{
	size_t	 ic;	/* Character position in the input buffer. */
	size_t	 vis;	/* Visual position of the current character. */
	size_t	 dv;	/* Visual width of the current character. */
	size_t	 vn;	/* Visual position of the next character. */

	vis = 0;
	for (ic = p->tcol->col; ic < nbr; ic++) {

		/*
		 * To avoid the printing of trailing whitespace,
		 * do not print whitespace right away, only count it.
		 */

		switch (p->tcol->buf[ic]) {
		case '\n':
		case ASCII_BREAK:
			continue;
		case '\t':
			vn = term_tab_next(vis);
			vbl += vn - vis;
			vis = vn;
			continue;
		case ' ':
		case ASCII_NBRSP:
			dv = (*p->width)(p, ' ');
			vbl += dv;
			vis += dv;
			continue;
		default:
			break;
		}

		/*
		 * We found a non-blank character to print,
		 * so write preceding white space now.
		 */

		if (vbl > 0) {
			(*p->advance)(p, vbl);
			p->viscol += vbl;
			vbl = 0;
		}

		/* Print the character and adjust the visual position. */

		(*p->letter)(p, p->tcol->buf[ic]);
		if (p->tcol->buf[ic] == '\b') {
			dv = (*p->width)(p, p->tcol->buf[ic - 1]);
			p->viscol -= dv;
			vis -= dv;
		} else {
			dv = (*p->width)(p, p->tcol->buf[ic]);
			p->viscol += dv;
			vis += dv;
		}
	}
	p->tcol->col = nbr;
}