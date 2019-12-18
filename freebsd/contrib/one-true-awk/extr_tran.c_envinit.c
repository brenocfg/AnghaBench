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
struct TYPE_3__ {char* sval; } ;
typedef  TYPE_1__ Cell ;

/* Variables and functions */
 int ARR ; 
 scalar_t__ ENVtab ; 
 int /*<<< orphan*/  NSYMTAB ; 
 int NUM ; 
 int STR ; 
 double atof (char*) ; 
 scalar_t__ is_number (char*) ; 
 scalar_t__ makesymtab (int /*<<< orphan*/ ) ; 
 TYPE_1__* setsymtab (char*,char*,double,int,scalar_t__) ; 
 char* strchr (char*,char) ; 
 scalar_t__ symtab ; 

void envinit(char **envp)	/* set up ENVIRON variable */
{
	Cell *cp;
	char *p;

	cp = setsymtab("ENVIRON", "", 0.0, ARR, symtab);
	ENVtab = makesymtab(NSYMTAB);
	cp->sval = (char *) ENVtab;
	for ( ; *envp; envp++) {
		if ((p = strchr(*envp, '=')) == NULL)
			continue;
		if( p == *envp ) /* no left hand side name in env string */
			continue;
		*p++ = 0;	/* split into two strings at = */
		if (is_number(p))
			setsymtab(*envp, p, atof(p), STR|NUM, ENVtab);
		else
			setsymtab(*envp, p, 0.0, STR, ENVtab);
		p[-1] = '=';	/* restore in case env is passed down to a shell */
	}
}