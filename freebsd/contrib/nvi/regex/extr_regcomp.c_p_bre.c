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
struct parse {scalar_t__ error; TYPE_1__* g; } ;
typedef  scalar_t__ sopno ;
struct TYPE_2__ {int /*<<< orphan*/  neol; int /*<<< orphan*/  iflags; int /*<<< orphan*/  nbol; } ;

/* Variables and functions */
 int /*<<< orphan*/  DROP (int) ; 
 scalar_t__ EAT (char) ; 
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HERE () ; 
 scalar_t__ MORE () ; 
 int /*<<< orphan*/  OBOL ; 
 int /*<<< orphan*/  OEOL ; 
 int /*<<< orphan*/  RECLIMIT ; 
 int /*<<< orphan*/  REG_EMPTY ; 
 scalar_t__ REG_ESPACE ; 
 int /*<<< orphan*/  REQUIRE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEETWO (int,int) ; 
 int /*<<< orphan*/  USEBOL ; 
 int /*<<< orphan*/  USEEOL ; 
 int p_simp_re (struct parse*,int,size_t) ; 

__attribute__((used)) static void
p_bre(struct parse *p,
    int end1,		/* first terminating character */
    int end2,		/* second terminating character */
    size_t reclimit)
{
	sopno start;
	int first = 1;			/* first subexpression? */
	int wasdollar = 0;

	if (reclimit++ > RECLIMIT || p->error == REG_ESPACE) {
		p->error = REG_ESPACE;
		return;
	}

	start = HERE();

	if (EAT('^')) {
		EMIT(OBOL, 0);
		p->g->iflags |= USEBOL;
		p->g->nbol++;
	}
	while (MORE() && !SEETWO(end1, end2)) {
		wasdollar = p_simp_re(p, first, reclimit);
		first = 0;
	}
	if (wasdollar) {	/* oops, that was a trailing anchor */
		DROP(1);
		EMIT(OEOL, 0);
		p->g->iflags |= USEEOL;
		p->g->neol++;
	}

	(void)REQUIRE(HERE() != start, REG_EMPTY);	/* require nonempty */
}