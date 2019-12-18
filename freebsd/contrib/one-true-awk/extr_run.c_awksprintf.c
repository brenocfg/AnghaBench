#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* sval; int /*<<< orphan*/  tval; } ;
struct TYPE_11__ {struct TYPE_11__* nnext; } ;
typedef  TYPE_1__ Node ;
typedef  TYPE_2__ Cell ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,...) ; 
 int /*<<< orphan*/  STR ; 
 TYPE_2__* execute (TYPE_1__*) ; 
 int format (char**,int*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  getsval (TYPE_2__*) ; 
 TYPE_2__* gettemp () ; 
 scalar_t__ malloc (int) ; 
 int recsize ; 
 int /*<<< orphan*/  tempfree (TYPE_2__*) ; 

Cell *awksprintf(Node **a, int n)		/* sprintf(a[0]) */
{
	Cell *x;
	Node *y;
	char *buf;
	int bufsz=3*recsize;

	if ((buf = (char *) malloc(bufsz)) == NULL)
		FATAL("out of memory in awksprintf");
	y = a[0]->nnext;
	x = execute(a[0]);
	if (format(&buf, &bufsz, getsval(x), y) == -1)
		FATAL("sprintf string %.30s... too long.  can't happen.", buf);
	tempfree(x);
	x = gettemp();
	x->sval = buf;
	x->tval = STR;
	return(x);
}