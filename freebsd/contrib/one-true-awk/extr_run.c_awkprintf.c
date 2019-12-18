#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* nnext; } ;
typedef  TYPE_1__ Node ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Cell ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,...) ; 
 int /*<<< orphan*/ * True ; 
 int /*<<< orphan*/ * execute (TYPE_1__*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 char* filename (int /*<<< orphan*/ *) ; 
 int format (char**,int*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getsval (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  ptoi (TYPE_1__*) ; 
 int recsize ; 
 int /*<<< orphan*/ * redirect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  tempfree (int /*<<< orphan*/ *) ; 

Cell *awkprintf(Node **a, int n)		/* printf */
{	/* a[0] is list of args, starting with format string */
	/* a[1] is redirection operator, a[2] is redirection file */
	FILE *fp;
	Cell *x;
	Node *y;
	char *buf;
	int len;
	int bufsz=3*recsize;

	if ((buf = (char *) malloc(bufsz)) == NULL)
		FATAL("out of memory in awkprintf");
	y = a[0]->nnext;
	x = execute(a[0]);
	if ((len = format(&buf, &bufsz, getsval(x), y)) == -1)
		FATAL("printf string %.30s... too long.  can't happen.", buf);
	tempfree(x);
	if (a[1] == NULL) {
		/* fputs(buf, stdout); */
		fwrite(buf, len, 1, stdout);
		if (ferror(stdout))
			FATAL("write error on stdout");
	} else {
		fp = redirect(ptoi(a[1]), a[2]);
		/* fputs(buf, fp); */
		fwrite(buf, len, 1, fp);
		fflush(fp);
		if (ferror(fp))
			FATAL("write error on %s", filename(fp));
	}
	free(buf);
	return(True);
}