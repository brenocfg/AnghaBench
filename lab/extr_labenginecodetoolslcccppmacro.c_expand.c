#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int hideset; scalar_t__ type; struct TYPE_18__* bp; struct TYPE_18__* tp; struct TYPE_18__* lp; } ;
typedef  TYPE_1__ Tokenrow ;
typedef  TYPE_1__ Token ;
struct TYPE_19__ {TYPE_1__* ap; int /*<<< orphan*/  vp; } ;
typedef  TYPE_3__ Nlist ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ NAME ; 
 int /*<<< orphan*/  NARG ; 
 int /*<<< orphan*/  copytokenrow (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doconcat (TYPE_1__*) ; 
 int /*<<< orphan*/  dofree (TYPE_1__*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char*) ; 
 int gatherargs (TYPE_1__*,TYPE_1__**,int*) ; 
 int /*<<< orphan*/  insertrow (TYPE_1__*,int,TYPE_1__*) ; 
 void* newhideset (int,TYPE_3__*) ; 
 int rowlen (TYPE_1__*) ; 
 int /*<<< orphan*/  substargs (TYPE_3__*,TYPE_1__*,TYPE_1__**) ; 
 int unionhideset (int,int) ; 

void
expand(Tokenrow *trp, Nlist *np)
{
	Tokenrow ntr;
	int ntokc, narg, i;
	Token *tp;
	Tokenrow *atr[NARG+1];
	int hs;

	copytokenrow(&ntr, np->vp);		/* copy macro value */
	if (np->ap==NULL)			/* parameterless */
		ntokc = 1;
	else {
		ntokc = gatherargs(trp, atr, &narg);
		if (narg<0) {			/* not actually a call (no '(') */
			trp->tp++;
			return;
		}
		if (narg != rowlen(np->ap)) {
			error(ERROR, "Disagreement in number of macro arguments");
			trp->tp->hideset = newhideset(trp->tp->hideset, np);
			trp->tp += ntokc;
			return;
		}
		substargs(np, &ntr, atr);	/* put args into replacement */
		for (i=0; i<narg; i++) {
			dofree(atr[i]->bp);
			dofree(atr[i]);
		}
	}
	doconcat(&ntr);				/* execute ## operators */
	hs = newhideset(trp->tp->hideset, np);
	for (tp=ntr.bp; tp<ntr.lp; tp++) {	/* distribute hidesets */
		if (tp->type==NAME) {
			if (tp->hideset==0)
				tp->hideset = hs;
			else
				tp->hideset = unionhideset(tp->hideset, hs);
		}
	}
	ntr.tp = ntr.bp;
	insertrow(trp, ntokc, &ntr);
	trp->tp -= rowlen(&ntr);
	dofree(ntr.bp);
}