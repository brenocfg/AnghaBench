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
struct TYPE_3__ {char* srcdir; char* name; char* objdir; scalar_t__ objpaths; scalar_t__ objs; struct TYPE_3__* next; } ;
typedef  TYPE_1__ prog_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* CRUNCH_VERSION ; 
 int MAXLINELEN ; 
 char* cachename ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int goterror ; 
 char* infilename ; 
 int /*<<< orphan*/  output_strlst (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* progs ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  status (char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

void
gen_specials_cache(void)
{
	FILE *cachef;
	prog_t *p;
	char line[MAXLINELEN];

	snprintf(line, MAXLINELEN, "generating %s", cachename);
	status(line);

	if ((cachef = fopen(cachename, "w")) == NULL) {
		warn("%s", cachename);
		goterror = 1;
		return;
	}

	fprintf(cachef, "# %s - parm cache generated from %s by crunchgen "
	    " %s\n\n",
	    cachename, infilename, CRUNCH_VERSION);

	for (p = progs; p != NULL; p = p->next) {
		fprintf(cachef, "\n");
		if (p->srcdir)
			fprintf(cachef, "special %s srcdir %s\n",
			    p->name, p->srcdir);
		if (p->objdir)
			fprintf(cachef, "special %s objdir %s\n",
			    p->name, p->objdir);
		if (p->objs) {
			fprintf(cachef, "special %s objs", p->name);
			output_strlst(cachef, p->objs);
		}
		if (p->objpaths) {
			fprintf(cachef, "special %s objpaths", p->name);
			output_strlst(cachef, p->objpaths);
		}
	}
	fclose(cachef);
}