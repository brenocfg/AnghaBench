#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* str; struct TYPE_4__* next; } ;
typedef  TYPE_1__ strlst_t ;
struct TYPE_5__ {char* ident; char* name; TYPE_1__* links; struct TYPE_5__* next; } ;
typedef  TYPE_2__ prog_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* CRUNCH_VERSION ; 
 int MAXLINELEN ; 
 char** crunched_skel ; 
 char* execfname ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int goterror ; 
 char* infilename ; 
 char* outcfname ; 
 TYPE_2__* progs ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  status (char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

void
gen_output_cfile(void)
{
	char **cp;
	FILE *outcf;
	prog_t *p;
	strlst_t *s;
	char line[MAXLINELEN];

	snprintf(line, MAXLINELEN, "generating %s", outcfname);
	status(line);

	if((outcf = fopen(outcfname, "w")) == NULL) {
		warn("%s", outcfname);
		goterror = 1;
		return;
	}

	fprintf(outcf,
	    "/* %s - generated from %s by crunchgen %s */\n",
	    outcfname, infilename, CRUNCH_VERSION);

	fprintf(outcf, "#define EXECNAME \"%s\"\n", execfname);
	for (cp = crunched_skel; *cp != NULL; cp++)
		fprintf(outcf, "%s\n", *cp);

	for (p = progs; p != NULL; p = p->next)
		fprintf(outcf, "extern int _crunched_%s_stub();\n", p->ident);

	fprintf(outcf, "\nstruct stub entry_points[] = {\n");
	for (p = progs; p != NULL; p = p->next) {
		fprintf(outcf, "\t{ \"%s\", _crunched_%s_stub },\n",
		    p->name, p->ident);
		for (s = p->links; s != NULL; s = s->next)
			fprintf(outcf, "\t{ \"%s\", _crunched_%s_stub },\n",
			    s->str, p->ident);
	}

	fprintf(outcf, "\t{ EXECNAME, crunched_main },\n");
	fprintf(outcf, "\t{ NULL, NULL }\n};\n");
	fclose(outcf);
}