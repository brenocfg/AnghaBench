#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fa ;
struct TYPE_9__ {int fval; int /*<<< orphan*/  tval; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ Cell ;
typedef  int /*<<< orphan*/  Awkfloat ;

/* Variables and functions */
 TYPE_1__* False ; 
 int MATCH ; 
 int MATCHFCN ; 
 int NOTMATCH ; 
 int /*<<< orphan*/  NUM ; 
 TYPE_1__* True ; 
 TYPE_1__* execute (int /*<<< orphan*/ *) ; 
 char* getsval (TYPE_1__*) ; 
 TYPE_1__* gettemp () ; 
 int /*<<< orphan*/ * makedfa (char*,int) ; 
 int match (int /*<<< orphan*/ *,char const*) ; 
 char* patbeg ; 
 scalar_t__ patlen ; 
 int pmatch (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  rlengthloc ; 
 int /*<<< orphan*/  rstartloc ; 
 int /*<<< orphan*/  setfval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,char const*) ; 
 int stub2 (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  tempfree (TYPE_1__*) ; 

Cell *matchop(Node **a, int n)	/* ~ and match() */
{
	Cell *x, *y;
	char *s, *t;
	int i;
	fa *pfa;
	int (*mf)(fa *, const char *) = match, mode = 0;

	if (n == MATCHFCN) {
		mf = pmatch;
		mode = 1;
	}
	x = execute(a[1]);	/* a[1] = target text */
	s = getsval(x);
	if (a[0] == NULL)	/* a[1] == 0: already-compiled reg expr */
		i = (*mf)((fa *) a[2], s);
	else {
		y = execute(a[2]);	/* a[2] = regular expr */
		t = getsval(y);
		pfa = makedfa(t, mode);
		i = (*mf)(pfa, s);
		tempfree(y);
	}
	tempfree(x);
	if (n == MATCHFCN) {
		int start = patbeg - s + 1;
		if (patlen < 0)
			start = 0;
		setfval(rstartloc, (Awkfloat) start);
		setfval(rlengthloc, (Awkfloat) patlen);
		x = gettemp();
		x->tval = NUM;
		x->fval = start;
		return x;
	} else if ((n == MATCH && i == 1) || (n == NOTMATCH && i == 0))
		return(True);
	else
		return(False);
}