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
struct TYPE_8__ {int /*<<< orphan*/  csub; int /*<<< orphan*/  ctype; int /*<<< orphan*/  nval; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ Cell ;
typedef  scalar_t__ Awkfloat ;

/* Variables and functions */
 int /*<<< orphan*/  CFLD ; 
 int /*<<< orphan*/  FATAL (char*,char*,...) ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  OCELL ; 
 TYPE_1__* execute (int /*<<< orphan*/ *) ; 
 TYPE_1__* fieldadr (int) ; 
 scalar_t__ getfval (TYPE_1__*) ; 
 char* getsval (TYPE_1__*) ; 
 int /*<<< orphan*/  is_number (char*) ; 
 int /*<<< orphan*/  tempfree (TYPE_1__*) ; 

Cell *indirect(Node **a, int n)	/* $( a[0] ) */
{
	Awkfloat val;
	Cell *x;
	int m;
	char *s;

	x = execute(a[0]);
	val = getfval(x);	/* freebsd: defend against super large field numbers */
	if ((Awkfloat)INT_MAX < val)
		FATAL("trying to access out of range field %s", x->nval);
	m = (int) val;
	if (m == 0 && !is_number(s = getsval(x)))	/* suspicion! */
		FATAL("illegal field $(%s), name \"%s\"", s, x->nval);
		/* BUG: can x->nval ever be null??? */
	tempfree(x);
	x = fieldadr(m);
	x->ctype = OCELL;	/* BUG?  why are these needed? */
	x->csub = CFLD;
	return(x);
}