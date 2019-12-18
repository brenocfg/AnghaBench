#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct termp {TYPE_2__* ps; } ;
struct TYPE_6__ {TYPE_1__* gly; } ;
struct TYPE_5__ {char last; size_t nextf; size_t lastf; size_t pscolnext; size_t pscol; } ;
struct TYPE_4__ {size_t wx; } ;

/* Variables and functions */
 size_t TERMFONT_NONE ; 
 TYPE_3__* fonts ; 
 int /*<<< orphan*/  ps_pclose (struct termp*) ; 
 int /*<<< orphan*/  ps_pletter (struct termp*,char) ; 
 int /*<<< orphan*/  ps_setfont (struct termp*,size_t) ; 

__attribute__((used)) static void
ps_plast(struct termp *p)
{
	size_t	 wx;

	if (p->ps->last == '\0')
		return;

	/* Check the font mode; open a new scope if it doesn't match. */

	if (p->ps->nextf != p->ps->lastf) {
		ps_pclose(p);
		ps_setfont(p, p->ps->nextf);
	}
	p->ps->nextf = TERMFONT_NONE;

	/*
	 * For an overstrike, if a previous character
	 * was wider, advance to center the new one.
	 */

	if (p->ps->pscolnext) {
		wx = fonts[p->ps->lastf].gly[(int)p->ps->last-32].wx;
		if (p->ps->pscol + wx < p->ps->pscolnext)
			p->ps->pscol = (p->ps->pscol +
			    p->ps->pscolnext - wx) / 2;
	}

	ps_pletter(p, p->ps->last);
	p->ps->last = '\0';

	/*
	 * For an overstrike, if a previous character
	 * was wider, advance to the end of the old one.
	 */

	if (p->ps->pscol < p->ps->pscolnext) {
		ps_pclose(p);
		p->ps->pscol = p->ps->pscolnext;
	}
}