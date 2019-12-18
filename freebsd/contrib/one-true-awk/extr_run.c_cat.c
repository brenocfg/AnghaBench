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
struct TYPE_7__ {char* sval; int /*<<< orphan*/  tval; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ Cell ;

/* Variables and functions */
 int /*<<< orphan*/  STR ; 
 int /*<<< orphan*/  adjbuf (char**,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* execute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getsval (TYPE_1__*) ; 
 TYPE_1__* gettemp () ; 
 int /*<<< orphan*/  recsize ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  tempfree (TYPE_1__*) ; 

Cell *cat(Node **a, int q)	/* a[0] cat a[1] */
{
	Cell *x, *y, *z;
	int n1, n2;
	char *s = NULL;
	int ssz = 0;

	x = execute(a[0]);
	n1 = strlen(getsval(x));
	adjbuf(&s, &ssz, n1 + 1, recsize, 0, "cat1");
	(void) strncpy(s, x->sval, ssz);

	y = execute(a[1]);
	n2 = strlen(getsval(y));
	adjbuf(&s, &ssz, n1 + n2 + 1, recsize, 0, "cat2");
	(void) strncpy(s + n1, y->sval, ssz - n1);

	tempfree(x);
	tempfree(y);

	z = gettemp();
	z->sval = s;
	z->tval = STR;

	return(z);
}