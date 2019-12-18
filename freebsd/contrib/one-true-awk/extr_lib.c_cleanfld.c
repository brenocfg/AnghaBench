#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* sval; int tval; } ;
typedef  TYPE_1__ Cell ;

/* Variables and functions */
 int DONTFREE ; 
 int FLD ; 
 int STR ; 
 TYPE_1__** fldtab ; 
 scalar_t__ freeable (TYPE_1__*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

void cleanfld(int n1, int n2)	/* clean out fields n1 .. n2 inclusive */
{				/* nvals remain intact */
	Cell *p;
	int i;

	for (i = n1; i <= n2; i++) {
		p = fldtab[i];
		if (freeable(p))
			xfree(p->sval);
		p->sval = "";
		p->tval = FLD | STR | DONTFREE;
	}
}