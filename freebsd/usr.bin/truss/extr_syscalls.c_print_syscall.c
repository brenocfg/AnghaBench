#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trussinfo {int /*<<< orphan*/  outfile; struct threadinfo* curthread; } ;
struct TYPE_4__ {int nargs; char** s_args; TYPE_1__* sc; } ;
struct threadinfo {TYPE_2__ cs; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 scalar_t__ fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int print_line_prefix (struct trussinfo*) ; 

void
print_syscall(struct trussinfo *trussinfo)
{
	struct threadinfo *t;
	const char *name;
	char **s_args;
	int i, len, nargs;

	t = trussinfo->curthread;

	name = t->cs.sc->name;
	nargs = t->cs.nargs;
	s_args = t->cs.s_args;

	len = print_line_prefix(trussinfo);
	len += fprintf(trussinfo->outfile, "%s(", name);

	for (i = 0; i < nargs; i++) {
		if (s_args[i] != NULL)
			len += fprintf(trussinfo->outfile, "%s", s_args[i]);
		else
			len += fprintf(trussinfo->outfile,
			    "<missing argument>");
		len += fprintf(trussinfo->outfile, "%s", i < (nargs - 1) ?
		    "," : "");
	}
	len += fprintf(trussinfo->outfile, ")");
	for (i = 0; i < 6 - (len / 8); i++)
		fprintf(trussinfo->outfile, "\t");
}