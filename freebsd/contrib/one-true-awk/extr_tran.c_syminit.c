#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {char* sval; int /*<<< orphan*/  fval; } ;

/* Variables and functions */
 int ARR ; 
 int /*<<< orphan*/  CCON ; 
 int CON ; 
 char** CONVFMT ; 
 int DONTFREE ; 
 char** FILENAME ; 
 int /*<<< orphan*/ * FNR ; 
 char** FS ; 
 int /*<<< orphan*/ * NF ; 
 int /*<<< orphan*/ * NR ; 
 int NUM ; 
 char** OFMT ; 
 char** OFS ; 
 char** ORS ; 
 int /*<<< orphan*/ * RLENGTH ; 
 char** RS ; 
 int /*<<< orphan*/ * RSTART ; 
 int STR ; 
 char** SUBSEP ; 
 int /*<<< orphan*/  celltonode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* fnrloc ; 
 TYPE_1__* fsloc ; 
 TYPE_1__* literal0 ; 
 TYPE_1__* nfloc ; 
 TYPE_1__* nrloc ; 
 TYPE_1__* nullloc ; 
 int /*<<< orphan*/  nullnode ; 
 TYPE_1__* ofsloc ; 
 TYPE_1__* orsloc ; 
 TYPE_1__* rlengthloc ; 
 TYPE_1__* rsloc ; 
 TYPE_1__* rstartloc ; 
 TYPE_1__* setsymtab (char*,char*,double,int,scalar_t__) ; 
 TYPE_1__* subseploc ; 
 scalar_t__ symtab ; 
 TYPE_1__* symtabloc ; 

void syminit(void)	/* initialize symbol table with builtin vars */
{
	literal0 = setsymtab("0", "0", 0.0, NUM|STR|CON|DONTFREE, symtab);
	/* this is used for if(x)... tests: */
	nullloc = setsymtab("$zero&null", "", 0.0, NUM|STR|CON|DONTFREE, symtab);
	nullnode = celltonode(nullloc, CCON);

	fsloc = setsymtab("FS", " ", 0.0, STR|DONTFREE, symtab);
	FS = &fsloc->sval;
	rsloc = setsymtab("RS", "\n", 0.0, STR|DONTFREE, symtab);
	RS = &rsloc->sval;
	ofsloc = setsymtab("OFS", " ", 0.0, STR|DONTFREE, symtab);
	OFS = &ofsloc->sval;
	orsloc = setsymtab("ORS", "\n", 0.0, STR|DONTFREE, symtab);
	ORS = &orsloc->sval;
	OFMT = &setsymtab("OFMT", "%.6g", 0.0, STR|DONTFREE, symtab)->sval;
	CONVFMT = &setsymtab("CONVFMT", "%.6g", 0.0, STR|DONTFREE, symtab)->sval;
	FILENAME = &setsymtab("FILENAME", "", 0.0, STR|DONTFREE, symtab)->sval;
	nfloc = setsymtab("NF", "", 0.0, NUM, symtab);
	NF = &nfloc->fval;
	nrloc = setsymtab("NR", "", 0.0, NUM, symtab);
	NR = &nrloc->fval;
	fnrloc = setsymtab("FNR", "", 0.0, NUM, symtab);
	FNR = &fnrloc->fval;
	subseploc = setsymtab("SUBSEP", "\034", 0.0, STR|DONTFREE, symtab);
	SUBSEP = &subseploc->sval;
	rstartloc = setsymtab("RSTART", "", 0.0, NUM, symtab);
	RSTART = &rstartloc->fval;
	rlengthloc = setsymtab("RLENGTH", "", 0.0, NUM, symtab);
	RLENGTH = &rlengthloc->fval;
	symtabloc = setsymtab("SYMTAB", "", 0.0, ARR, symtab);
	symtabloc->sval = (char *) symtab;
}