#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* nnext; } ;
typedef  TYPE_1__ Node ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Cell ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * True ; 
 int /*<<< orphan*/ * execute (TYPE_1__*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpssval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getsval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofsloc ; 
 int /*<<< orphan*/  orsloc ; 
 int /*<<< orphan*/  ptoi (TYPE_1__*) ; 
 int /*<<< orphan*/ * redirect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  tempfree (int /*<<< orphan*/ *) ; 

Cell *printstat(Node **a, int n)	/* print a[0] */
{
	Node *x;
	Cell *y;
	FILE *fp;

	if (a[1] == NULL)	/* a[1] is redirection operator, a[2] is file */
		fp = stdout;
	else
		fp = redirect(ptoi(a[1]), a[2]);
	for (x = a[0]; x != NULL; x = x->nnext) {
		y = execute(x);
		fputs(getpssval(y), fp);
		tempfree(y);
		if (x->nnext == NULL)
			fputs(getsval(orsloc), fp);
		else
			fputs(getsval(ofsloc), fp);
	}
	if (a[1] != NULL)
		fflush(fp);
	if (ferror(fp))
		FATAL("write error on %s", filename(fp));
	return(True);
}