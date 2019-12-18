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
typedef  scalar_t__ Awkfloat ;

/* Variables and functions */
 int POSTINCR ; 
 int PREDECR ; 
 int PREINCR ; 
 int /*<<< orphan*/ * execute (int /*<<< orphan*/ *) ; 
 scalar_t__ getfval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gettemp () ; 
 int /*<<< orphan*/  setfval (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tempfree (int /*<<< orphan*/ *) ; 

Cell *incrdecr(Node **a, int n)		/* a[0]++, etc. */
{
	Cell *x, *z;
	int k;
	Awkfloat xf;

	x = execute(a[0]);
	xf = getfval(x);
	k = (n == PREINCR || n == POSTINCR) ? 1 : -1;
	if (n == PREINCR || n == PREDECR) {
		setfval(x, xf + k);
		return(x);
	}
	z = gettemp();
	setfval(z, xf);
	setfval(x, xf + k);
	tempfree(x);
	return(z);
}