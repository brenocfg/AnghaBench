#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int size; TYPE_1__** tab; } ;
struct TYPE_13__ {struct TYPE_13__* cnext; int /*<<< orphan*/  nval; scalar_t__ sval; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ Cell ;
typedef  TYPE_2__ Array ;

/* Variables and functions */
 TYPE_1__* True ; 
 TYPE_1__* execute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isarr (TYPE_1__*) ; 
 scalar_t__ isbreak (TYPE_1__*) ; 
 scalar_t__ isexit (TYPE_1__*) ; 
 scalar_t__ isnext (TYPE_1__*) ; 
 scalar_t__ isret (TYPE_1__*) ; 
 int /*<<< orphan*/  setsval (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tempfree (TYPE_1__*) ; 

Cell *instat(Node **a, int n)	/* for (a[0] in a[1]) a[2] */
{
	Cell *x, *vp, *arrayp, *cp, *ncp;
	Array *tp;
	int i;

	vp = execute(a[0]);
	arrayp = execute(a[1]);
	if (!isarr(arrayp)) {
		return True;
	}
	tp = (Array *) arrayp->sval;
	tempfree(arrayp);
	for (i = 0; i < tp->size; i++) {	/* this routine knows too much */
		for (cp = tp->tab[i]; cp != NULL; cp = ncp) {
			setsval(vp, cp->nval);
			ncp = cp->cnext;
			x = execute(a[2]);
			if (isbreak(x)) {
				tempfree(vp);
				return True;
			}
			if (isnext(x) || isexit(x) || isret(x)) {
				tempfree(vp);
				return(x);
			}
			tempfree(x);
		}
	}
	return True;
}