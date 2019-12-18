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
struct TYPE_3__ {char* name; char* ident; struct TYPE_3__* next; } ;
typedef  TYPE_1__ prog_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ buildopts ; 
 char* execfname ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ libs ; 
 scalar_t__ libs_so ; 
 scalar_t__ makeobj ; 
 char* objprefix ; 
 int /*<<< orphan*/  output_strlst (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* progs ; 
 scalar_t__ subtract_strlst (scalar_t__*,scalar_t__*) ; 

void
top_makefile_rules(FILE *outmk)
{
	prog_t *p;

	fprintf(outmk, "LD?= ld\n");
	if ( subtract_strlst(&libs, &libs_so) )
		fprintf(outmk, "# NOTE: Some LIBS declarations below overridden by LIBS_SO\n");

	fprintf(outmk, "LIBS+=");
	output_strlst(outmk, libs);

	fprintf(outmk, "LIBS_SO+=");
	output_strlst(outmk, libs_so);

	if (makeobj) {
		fprintf(outmk, "MAKEOBJDIRPREFIX?=%s\n", objprefix);
		fprintf(outmk, "MAKEENV=env MAKEOBJDIRPREFIX=$(MAKEOBJDIRPREFIX)\n");
		fprintf(outmk, "CRUNCHMAKE=$(MAKEENV) $(MAKE)\n");
	} else {
		fprintf(outmk, "CRUNCHMAKE=$(MAKE)\n");
	}

	if (buildopts) {
		fprintf(outmk, "BUILDOPTS+=");
		output_strlst(outmk, buildopts);
	}

	fprintf(outmk, "CRUNCHED_OBJS=");
	for (p = progs; p != NULL; p = p->next)
		fprintf(outmk, " %s.lo", p->name);
	fprintf(outmk, "\n");

	fprintf(outmk, "SUBMAKE_TARGETS=");
	for (p = progs; p != NULL; p = p->next)
		fprintf(outmk, " %s_make", p->ident);
	fprintf(outmk, "\nSUBCLEAN_TARGETS=");
	for (p = progs; p != NULL; p = p->next)
		fprintf(outmk, " %s_clean", p->ident);
	fprintf(outmk, "\n\n");

	fprintf(outmk, "all: objs exe\nobjs: $(SUBMAKE_TARGETS)\n");
	fprintf(outmk, "exe: %s\n", execfname);
	fprintf(outmk, "%s: %s.o $(CRUNCHED_OBJS) $(SUBMAKE_TARGETS)\n", execfname, execfname);
	fprintf(outmk, ".if defined(LIBS_SO) && !empty(LIBS_SO)\n");
	fprintf(outmk, "\t$(CC) -o %s %s.o $(CRUNCHED_OBJS) \\\n",
	    execfname, execfname);
	fprintf(outmk, "\t\t-Xlinker -Bstatic $(LIBS) \\\n");
	fprintf(outmk, "\t\t-Xlinker -Bdynamic $(LIBS_SO)\n");
	fprintf(outmk, ".else\n");
	fprintf(outmk, "\t$(CC) -static -o %s %s.o $(CRUNCHED_OBJS) $(LIBS)\n",
	    execfname, execfname);
	fprintf(outmk, ".endif\n");
	fprintf(outmk, "realclean: clean subclean\n");
	fprintf(outmk, "clean:\n\trm -f %s *.lo *.o *_stub.c\n", execfname);
	fprintf(outmk, "subclean: $(SUBCLEAN_TARGETS)\n");
}