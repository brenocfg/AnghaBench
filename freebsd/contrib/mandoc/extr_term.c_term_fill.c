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
struct termp {size_t (* width ) (struct termp*,char) ;TYPE_1__* tcol; } ;
struct TYPE_2__ {size_t col; size_t lastcol; int* buf; } ;

/* Variables and functions */
#define  ASCII_BREAK 130 
#define  ASCII_HYPH 129 
#define  ASCII_NBRSP 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t stub1 (struct termp*,char) ; 
 size_t stub2 (struct termp*,char) ; 
 size_t stub3 (struct termp*,char) ; 
 size_t stub4 (struct termp*,char) ; 
 size_t term_tab_next (size_t) ; 

__attribute__((used)) static void
term_fill(struct termp *p, size_t *nbr, size_t *vbr, size_t vtarget)
{
	size_t	 ic;        /* Character position in the input buffer. */
	size_t	 vis;       /* Visual position of the current character. */
	size_t	 vn;        /* Visual position of the next character. */
	int	 breakline; /* Break at the end of this word. */
	int	 graph;     /* Last character was non-blank. */

	*nbr = *vbr = vis = 0;
	breakline = graph = 0;
	for (ic = p->tcol->col; ic < p->tcol->lastcol; ic++) {
		switch (p->tcol->buf[ic]) {
		case '\b':  /* Escape \o (overstrike) or backspace markup. */
			assert(ic > 0);
			vis -= (*p->width)(p, p->tcol->buf[ic - 1]);
			continue;

		case '\t':  /* Normal ASCII whitespace. */
		case ' ':
		case ASCII_BREAK:  /* Escape \: (breakpoint). */
			switch (p->tcol->buf[ic]) {
			case '\t':
				vn = term_tab_next(vis);
				break;
			case ' ':
				vn = vis + (*p->width)(p, ' ');
				break;
			case ASCII_BREAK:
				vn = vis;
				break;
			default:
				abort();
			}
			/* Can break at the end of a word. */
			if (breakline || vn > vtarget)
				break;
			if (graph) {
				*nbr = ic;
				*vbr = vis;
				graph = 0;
			}
			vis = vn;
			continue;

		case '\n':  /* Escape \p (break at the end of the word). */
			breakline = 1;
			continue;

		case ASCII_HYPH:  /* Breakable hyphen. */
			graph = 1;
			/*
			 * We are about to decide whether to break the
			 * line or not, so we no longer need this hyphen
			 * to be marked as breakable.  Put back a real
			 * hyphen such that we get the correct width.
			 */
			p->tcol->buf[ic] = '-';
			vis += (*p->width)(p, '-');
			if (vis > vtarget) {
				ic++;
				break;
			}
			*nbr = ic + 1;
			*vbr = vis;
			continue;

		case ASCII_NBRSP:  /* Non-breakable space. */
			p->tcol->buf[ic] = ' ';
			/* FALLTHROUGH */
		default:  /* Printable character. */
			graph = 1;
			vis += (*p->width)(p, p->tcol->buf[ic]);
			if (vis > vtarget && *nbr > 0)
				return;
			continue;
		}
		break;
	}

	/*
	 * If the last word extends to the end of the field without any
	 * trailing whitespace, the loop could not check yet whether it
	 * can remain on this line.  So do the check now.
	 */

	if (graph && (vis <= vtarget || *nbr == 0)) {
		*nbr = ic;
		*vbr = vis;
	}
}