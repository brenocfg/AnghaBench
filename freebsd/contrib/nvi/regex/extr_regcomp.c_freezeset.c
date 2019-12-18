#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uch ;
struct parse {TYPE_1__* g; } ;
struct TYPE_7__ {scalar_t__ hash; } ;
typedef  TYPE_2__ cset ;
struct TYPE_6__ {size_t ncsets; TYPE_2__* sets; int /*<<< orphan*/  csetsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIN (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  freeset (struct parse*,TYPE_2__*) ; 

__attribute__((used)) static int			/* set number */
freezeset(struct parse *p, cset *cs)
{
	uch h = cs->hash;
	size_t i;
	cset *top = &p->g->sets[p->g->ncsets];
	cset *cs2;
	size_t css = (size_t)p->g->csetsize;

	/* look for an earlier one which is the same */
	for (cs2 = &p->g->sets[0]; cs2 < top; cs2++)
		if (cs2->hash == h && cs2 != cs) {
			/* maybe */
			for (i = 0; i < css; i++)
				if (!!CHIN(cs2, i) != !!CHIN(cs, i))
					break;		/* no */
			if (i == css)
				break;			/* yes */
		}

	if (cs2 < top) {	/* found one */
		freeset(p, cs);
		cs = cs2;
	}

	return((int)(cs - p->g->sets));
}