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
struct re_guts {int /*<<< orphan*/  iflags; int /*<<< orphan*/ * strip; } ;
struct parse {scalar_t__ error; } ;
typedef  scalar_t__ sopno ;
typedef  int /*<<< orphan*/  sop ;

/* Variables and functions */
 int /*<<< orphan*/  BAD ; 
 int OEND ; 
 int OP (int /*<<< orphan*/ ) ; 
#define  OPLUS_ 129 
#define  O_PLUS 128 

__attribute__((used)) static sopno			/* nesting depth */
pluscount(struct parse *p, struct re_guts *g)
{
	sop *scan;
	sop s;
	sopno plusnest = 0;
	sopno maxnest = 0;

	if (p->error != 0)
		return(0);	/* there may not be an OEND */

	scan = g->strip + 1;
	do {
		s = *scan++;
		switch (OP(s)) {
		case OPLUS_:
			plusnest++;
			break;
		case O_PLUS:
			if (plusnest > maxnest)
				maxnest = plusnest;
			plusnest--;
			break;
		}
	} while (OP(s) != OEND);
	if (plusnest != 0)
		g->iflags |= BAD;
	return(maxnest);
}