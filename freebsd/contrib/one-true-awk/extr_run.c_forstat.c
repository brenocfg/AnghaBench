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
 int /*<<< orphan*/ * True ; 
 int /*<<< orphan*/ * execute (int /*<<< orphan*/ *) ; 
 scalar_t__ isbreak (int /*<<< orphan*/ *) ; 
 scalar_t__ isexit (int /*<<< orphan*/ *) ; 
 scalar_t__ isnext (int /*<<< orphan*/ *) ; 
 scalar_t__ isret (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  istrue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tempfree (int /*<<< orphan*/ *) ; 

Cell *forstat(Node **a, int n)	/* for (a[0]; a[1]; a[2]) a[3] */
{
	Cell *x;

	x = execute(a[0]);
	tempfree(x);
	for (;;) {
		if (a[1]!=NULL) {
			x = execute(a[1]);
			if (!istrue(x)) return(x);
			else tempfree(x);
		}
		x = execute(a[3]);
		if (isbreak(x))		/* turn off break */
			return True;
		if (isnext(x) || isexit(x) || isret(x))
			return(x);
		tempfree(x);
		x = execute(a[2]);
		tempfree(x);
	}
}