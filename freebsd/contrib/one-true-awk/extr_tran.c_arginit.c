#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* sval; int /*<<< orphan*/  fval; } ;
typedef  TYPE_1__ Cell ;
typedef  double Awkfloat ;

/* Variables and functions */
 int /*<<< orphan*/ * ARGC ; 
 scalar_t__ ARGVtab ; 
 int ARR ; 
 int /*<<< orphan*/  NSYMTAB ; 
 int NUM ; 
 int STR ; 
 double atof (char*) ; 
 scalar_t__ is_number (char*) ; 
 scalar_t__ makesymtab (int /*<<< orphan*/ ) ; 
 TYPE_1__* setsymtab (char*,char*,double,int,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ symtab ; 

void arginit(int ac, char **av)	/* set up ARGV and ARGC */
{
	Cell *cp;
	int i;
	char temp[50];

	ARGC = &setsymtab("ARGC", "", (Awkfloat) ac, NUM, symtab)->fval;
	cp = setsymtab("ARGV", "", 0.0, ARR, symtab);
	ARGVtab = makesymtab(NSYMTAB);	/* could be (int) ARGC as well */
	cp->sval = (char *) ARGVtab;
	for (i = 0; i < ac; i++) {
		sprintf(temp, "%d", i);
		if (is_number(*av))
			setsymtab(temp, *av, atof(*av), STR|NUM, ARGVtab);
		else
			setsymtab(temp, *av, 0.0, STR, ARGVtab);
		av++;
	}
}