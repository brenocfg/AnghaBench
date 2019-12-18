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
struct TYPE_9__ {int /*<<< orphan*/  tval; int /*<<< orphan*/  sval; void* fval; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Cell ;
typedef  int /*<<< orphan*/  Awkfloat ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*) ; 
 int LE ; 
 int /*<<< orphan*/  NUM ; 
 void* atof (int /*<<< orphan*/ ) ; 
 TYPE_1__* execute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getrec (char**,int*,int) ; 
 int /*<<< orphan*/  getsval (TYPE_1__*) ; 
 TYPE_1__* gettemp () ; 
 scalar_t__ is_number (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/ * openfile (int,int /*<<< orphan*/ ) ; 
 int ptoi (int /*<<< orphan*/ *) ; 
 int readrec (char**,int*,int /*<<< orphan*/ *) ; 
 char* record ; 
 int recsize ; 
 int /*<<< orphan*/  setfval (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsval (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  tempfree (TYPE_1__*) ; 

Cell *awkgetline(Node **a, int n)	/* get next line from specific input */
{		/* a[0] is variable, a[1] is operator, a[2] is filename */
	Cell *r, *x;
	extern Cell **fldtab;
	FILE *fp;
	char *buf;
	int bufsize = recsize;
	int mode;

	if ((buf = (char *) malloc(bufsize)) == NULL)
		FATAL("out of memory in getline");

	fflush(stdout);	/* in case someone is waiting for a prompt */
	r = gettemp();
	if (a[1] != NULL) {		/* getline < file */
		x = execute(a[2]);		/* filename */
		mode = ptoi(a[1]);
		if (mode == '|')		/* input pipe */
			mode = LE;	/* arbitrary flag */
		fp = openfile(mode, getsval(x));
		tempfree(x);
		if (fp == NULL)
			n = -1;
		else
			n = readrec(&buf, &bufsize, fp);
		if (n <= 0) {
			;
		} else if (a[0] != NULL) {	/* getline var <file */
			x = execute(a[0]);
			setsval(x, buf);
			if (is_number(x->sval)) {
				x->fval = atof(x->sval);
				x->tval |= NUM;
			}
			tempfree(x);
		} else {			/* getline <file */
			setsval(fldtab[0], buf);
			if (is_number(fldtab[0]->sval)) {
				fldtab[0]->fval = atof(fldtab[0]->sval);
				fldtab[0]->tval |= NUM;
			}
		}
	} else {			/* bare getline; use current input */
		if (a[0] == NULL)	/* getline */
			n = getrec(&record, &recsize, 1);
		else {			/* getline var */
			n = getrec(&buf, &bufsize, 0);
			x = execute(a[0]);
			setsval(x, buf);
			if (is_number(x->sval)) {
				x->fval = atof(x->sval);
				x->tval |= NUM;
			}
			tempfree(x);
		}
	}
	setfval(r, (Awkfloat) n);
	free(buf);
	return r;
}