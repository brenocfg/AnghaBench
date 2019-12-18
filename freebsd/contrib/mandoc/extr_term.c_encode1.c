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
struct termp {int flags; int col; int* fontq; size_t fonti; TYPE_1__* tcol; int /*<<< orphan*/  (* letter ) (struct termp*,int) ;} ;
typedef  enum termfont { ____Placeholder_termfont } termfont ;
struct TYPE_2__ {int maxcols; char* buf; int lastcol; } ;

/* Variables and functions */
 int ASCII_HYPH ; 
 int ASCII_NBRSP ; 
 int TERMFONT_BI ; 
 int TERMFONT_BOLD ; 
 int TERMFONT_NONE ; 
 int TERMFONT_UNDER ; 
 int TERMP_BACKAFTER ; 
 int TERMP_BACKBEFORE ; 
 int TERMP_NOBUF ; 
 int /*<<< orphan*/  adjbuf (TYPE_1__*,int) ; 
 scalar_t__ isgraph (int) ; 
 int /*<<< orphan*/  stub1 (struct termp*,int) ; 

__attribute__((used)) static void
encode1(struct termp *p, int c)
{
	enum termfont	  f;

	if (p->flags & TERMP_NOBUF) {
		(*p->letter)(p, c);
		return;
	}

	if (p->col + 7 >= p->tcol->maxcols)
		adjbuf(p->tcol, p->col + 7);

	f = (c == ASCII_HYPH || c > 127 || isgraph(c)) ?
	    p->fontq[p->fonti] : TERMFONT_NONE;

	if (p->flags & TERMP_BACKBEFORE) {
		if (p->tcol->buf[p->col - 1] == ' ' ||
		    p->tcol->buf[p->col - 1] == '\t')
			p->col--;
		else
			p->tcol->buf[p->col++] = '\b';
		p->flags &= ~TERMP_BACKBEFORE;
	}
	if (f == TERMFONT_UNDER || f == TERMFONT_BI) {
		p->tcol->buf[p->col++] = '_';
		p->tcol->buf[p->col++] = '\b';
	}
	if (f == TERMFONT_BOLD || f == TERMFONT_BI) {
		if (c == ASCII_HYPH)
			p->tcol->buf[p->col++] = '-';
		else
			p->tcol->buf[p->col++] = c;
		p->tcol->buf[p->col++] = '\b';
	}
	if (p->tcol->lastcol <= p->col || (c != ' ' && c != ASCII_NBRSP))
		p->tcol->buf[p->col] = c;
	if (p->tcol->lastcol < ++p->col)
		p->tcol->lastcol = p->col;
	if (p->flags & TERMP_BACKAFTER) {
		p->flags |= TERMP_BACKBEFORE;
		p->flags &= ~TERMP_BACKAFTER;
	}
}