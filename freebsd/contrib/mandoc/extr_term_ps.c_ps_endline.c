#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct termp {scalar_t__ ti; TYPE_2__* tcol; TYPE_1__* ps; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
struct TYPE_3__ {int flags; scalar_t__ psrow; scalar_t__ lineheight; scalar_t__ bottom; int /*<<< orphan*/  left; int /*<<< orphan*/  pscol; } ;

/* Variables and functions */
 int PS_MARGINS ; 
 int PS_NEWPAGE ; 
 int /*<<< orphan*/  ps_closepage (struct termp*) ; 
 int /*<<< orphan*/  ps_pclose (struct termp*) ; 
 int /*<<< orphan*/  ps_plast (struct termp*) ; 

__attribute__((used)) static void
ps_endline(struct termp *p)
{

	/* Close out any scopes we have open: we're at eoln. */

	ps_plast(p);
	ps_pclose(p);

	/*
	 * If we're in the margin, don't try to recalculate our current
	 * row.  XXX: if the column tries to be fancy with multiple
	 * lines, we'll do nasty stuff.
	 */

	if (PS_MARGINS & p->ps->flags)
		return;

	/* Left-justify. */

	p->ps->pscol = p->ps->left;

	/* If we haven't printed anything, return. */

	if (PS_NEWPAGE & p->ps->flags)
		return;

	/*
	 * Put us down a line.  If we're at the page bottom, spit out a
	 * showpage and restart our row.
	 */

	if (p->ps->psrow >= p->ps->lineheight + p->ps->bottom) {
		p->ps->psrow -= p->ps->lineheight;
		return;
	}

	ps_closepage(p);

	p->tcol->offset -= p->ti;
	p->ti = 0;
}