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
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Cell ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*) ; 
 int /*<<< orphan*/ * True ; 
 int /*<<< orphan*/  env ; 
 int /*<<< orphan*/ * execute (int /*<<< orphan*/ *) ; 
 scalar_t__ getrec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ isbreak (int /*<<< orphan*/ *) ; 
 scalar_t__ iscont (int /*<<< orphan*/ *) ; 
 scalar_t__ isexit (int /*<<< orphan*/ *) ; 
 scalar_t__ isjump (int /*<<< orphan*/ *) ; 
 scalar_t__ isnext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record ; 
 int /*<<< orphan*/  recsize ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tempfree (int /*<<< orphan*/ *) ; 

Cell *program(Node **a, int n)	/* execute an awk program */
{				/* a[0] = BEGIN, a[1] = body, a[2] = END */
	Cell *x;

	if (setjmp(env) != 0)
		goto ex;
	if (a[0]) {		/* BEGIN */
		x = execute(a[0]);
		if (isexit(x))
			return(True);
		if (isjump(x))
			FATAL("illegal break, continue, next or nextfile from BEGIN");
		tempfree(x);
	}
	if (a[1] || a[2])
		while (getrec(&record, &recsize, 1) > 0) {
			x = execute(a[1]);
			if (isexit(x))
				break;
			tempfree(x);
		}
  ex:
	if (setjmp(env) != 0)	/* handles exit within END */
		goto ex1;
	if (a[2]) {		/* END */
		x = execute(a[2]);
		if (isbreak(x) || isnext(x) || iscont(x))
			FATAL("illegal break, continue, next or nextfile from END");
		tempfree(x);
	}
  ex1:
	return(True);
}