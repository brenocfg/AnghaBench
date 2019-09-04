#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* tp; TYPE_2__* bp; TYPE_2__* lp; } ;
typedef  TYPE_1__ Tokenrow ;
struct TYPE_15__ {scalar_t__ type; } ;
typedef  TYPE_2__ Token ;
typedef  int /*<<< orphan*/  Nlist ;

/* Variables and functions */
 scalar_t__ DSHARP ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ NAME ; 
 scalar_t__ SHARP ; 
 int /*<<< orphan*/  copytokenrow (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dofree (TYPE_2__*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  expandrow (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  insertrow (TYPE_1__*,int,TYPE_1__*) ; 
 int lookuparg (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__* stringify (TYPE_1__*) ; 

void
substargs(Nlist *np, Tokenrow *rtr, Tokenrow **atr)
{
	Tokenrow tatr;
	Token *tp;
	int ntok, argno;

	for (rtr->tp=rtr->bp; rtr->tp<rtr->lp; ) {
		if (rtr->tp->type==SHARP) {	/* string operator */
			tp = rtr->tp;
			rtr->tp += 1;
			if ((argno = lookuparg(np, rtr->tp))<0) {
				error(ERROR, "# not followed by macro parameter");
				continue;
			}
			ntok = 1 + (rtr->tp - tp);
			rtr->tp = tp;
			insertrow(rtr, ntok, stringify(atr[argno]));
			continue;
		}
		if (rtr->tp->type==NAME
		 && (argno = lookuparg(np, rtr->tp)) >= 0) {
			if ((rtr->tp+1)->type==DSHARP
			 || (rtr->tp!=rtr->bp && (rtr->tp-1)->type==DSHARP))
				insertrow(rtr, 1, atr[argno]);
			else {
				copytokenrow(&tatr, atr[argno]);
				expandrow(&tatr, "<macro>");
				insertrow(rtr, 1, &tatr);
				dofree(tatr.bp);
			}
			continue;
		}
		rtr->tp++;
	}
}