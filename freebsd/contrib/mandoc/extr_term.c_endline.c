#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct termp {int flags; scalar_t__ viscol; scalar_t__ maxrmargin; int /*<<< orphan*/  (* endline ) (struct termp*) ;scalar_t__ minbl; int /*<<< orphan*/ * mc; int /*<<< orphan*/  (* advance ) (struct termp*,scalar_t__) ;} ;

/* Variables and functions */
 int TERMP_ENDMC ; 
 int TERMP_NEWMC ; 
 int TERMP_NOBUF ; 
 int TERMP_NOSPACE ; 
 int /*<<< orphan*/  stub1 (struct termp*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct termp*) ; 
 int /*<<< orphan*/  term_word (struct termp*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
endline(struct termp *p)
{
	if ((p->flags & (TERMP_NEWMC | TERMP_ENDMC)) == TERMP_ENDMC) {
		p->mc = NULL;
		p->flags &= ~TERMP_ENDMC;
	}
	if (p->mc != NULL) {
		if (p->viscol && p->maxrmargin >= p->viscol)
			(*p->advance)(p, p->maxrmargin - p->viscol + 1);
		p->flags |= TERMP_NOBUF | TERMP_NOSPACE;
		term_word(p, p->mc);
		p->flags &= ~(TERMP_NOBUF | TERMP_NEWMC);
	}
	p->viscol = 0;
	p->minbl = 0;
	(*p->endline)(p);
}