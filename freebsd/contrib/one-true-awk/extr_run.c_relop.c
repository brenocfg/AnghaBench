#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int tval; scalar_t__ fval; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ Cell ;
typedef  scalar_t__ Awkfloat ;

/* Variables and functions */
#define  EQ 133 
 int /*<<< orphan*/  FATAL (char*,int) ; 
 TYPE_1__* False ; 
#define  GE 132 
#define  GT 131 
#define  LE 130 
#define  LT 129 
#define  NE 128 
 int NUM ; 
 TYPE_1__* True ; 
 TYPE_1__* execute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getsval (TYPE_1__*) ; 
 int strcoll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tempfree (TYPE_1__*) ; 

Cell *relop(Node **a, int n)	/* a[0 < a[1], etc. */
{
	int i;
	Cell *x, *y;
	Awkfloat j;

	x = execute(a[0]);
	y = execute(a[1]);
	if (x->tval&NUM && y->tval&NUM) {
		j = x->fval - y->fval;
		i = j<0? -1: (j>0? 1: 0);
	} else {
		i = strcoll(getsval(x), getsval(y));
	}
	tempfree(x);
	tempfree(y);
	switch (n) {
	case LT:	if (i<0) return(True);
			else return(False);
	case LE:	if (i<=0) return(True);
			else return(False);
	case NE:	if (i!=0) return(True);
			else return(False);
	case EQ:	if (i == 0) return(True);
			else return(False);
	case GE:	if (i>=0) return(True);
			else return(False);
	case GT:	if (i>0) return(True);
			else return(False);
	default:	/* can't happen */
		FATAL("unknown relational operator %d", n);
	}
	return 0;	/*NOTREACHED*/
}