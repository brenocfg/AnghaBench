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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ prog_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* CRUNCH_VERSION ; 
 int MAXLINELEN ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int goterror ; 
 char* infilename ; 
 char* outhdrname ; 
 char* outmkname ; 
 int /*<<< orphan*/  prog_makefile_rules (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* progs ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  status (char*) ; 
 int /*<<< orphan*/  top_makefile_rules (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

void
gen_output_makefile(void)
{
	prog_t *p;
	FILE *outmk;
	char line[MAXLINELEN];

	snprintf(line, MAXLINELEN, "generating %s", outmkname);
	status(line);

	if ((outmk = fopen(outmkname, "w")) == NULL) {
		warn("%s", outmkname);
		goterror = 1;
		return;
	}

	fprintf(outmk, "# %s - generated from %s by crunchgen %s\n\n",
	    outmkname, infilename, CRUNCH_VERSION);

	if (outhdrname[0] != '\0')
		fprintf(outmk, ".include \"%s\"\n", outhdrname);

	top_makefile_rules(outmk);
	for (p = progs; p != NULL; p = p->next)
		prog_makefile_rules(outmk, p);

	fprintf(outmk, "\n# ========\n");
	fclose(outmk);
}