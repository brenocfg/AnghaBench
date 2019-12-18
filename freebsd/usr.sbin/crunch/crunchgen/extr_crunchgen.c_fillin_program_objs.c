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
struct TYPE_5__ {char* objvar; char* srcdir; char* ident; int /*<<< orphan*/  objs; TYPE_1__* buildopts; } ;
typedef  TYPE_2__ prog_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXLINELEN ; 
 int /*<<< orphan*/  add_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ buildopts ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int goterror ; 
 scalar_t__ isspace (unsigned char) ; 
 int mkstemp (char*) ; 
 char* outhdrname ; 
 int /*<<< orphan*/  output_strlst (int /*<<< orphan*/ *,scalar_t__) ; 
 char* path_make ; 
 int pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* tempfname ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

void
fillin_program_objs(prog_t *p, char *path)
{
	char *obj, *cp;
	int fd, rc;
	FILE *f;
	char *objvar="OBJS";
	strlst_t *s;
	char line[MAXLINELEN];

	/* discover the objs from the srcdir Makefile */

	if ((fd = mkstemp(tempfname)) == -1) {
		perror(tempfname);
		exit(1);
	}
	if ((f = fdopen(fd, "w")) == NULL) {
		warn("%s", tempfname);
		goterror = 1;
		return;
	}
	if (p->objvar)
		objvar = p->objvar;

	/*
	* XXX include outhdrname (e.g. to contain Make variables)
	*/
	if (outhdrname[0] != '\0')
		fprintf(f, ".include \"%s\"\n", outhdrname);
	fprintf(f, ".include \"%s\"\n", path);
	fprintf(f, ".POSIX:\n");
	if (buildopts) {
		fprintf(f, "BUILDOPTS+=");
		output_strlst(f, buildopts);
	}
	fprintf(f, ".if defined(PROG)\n");
	fprintf(f, "%s?=${PROG}.o\n", objvar);
	fprintf(f, ".endif\n");
	fprintf(f, "loop:\n\t@echo 'OBJS= '${%s}\n", objvar);

	fprintf(f, "crunchgen_objs:\n"
	    "\t@cd %s && %s -f %s $(BUILDOPTS) $(%s_OPTS)",
	    p->srcdir, path_make, tempfname, p->ident);
	for (s = p->buildopts; s != NULL; s = s->next)
		fprintf(f, " %s", s->str);
	fprintf(f, " loop\n");

	fclose(f);

	snprintf(line, MAXLINELEN, "cd %s && %s -f %s -B crunchgen_objs",
	     p->srcdir, path_make, tempfname);
	if ((f = popen(line, "r")) == NULL) {
		warn("submake pipe");
		goterror = 1;
		return;
	}

	while(fgets(line, MAXLINELEN, f)) {
		if (strncmp(line, "OBJS= ", 6)) {
			warnx("make error: %s", line);
			goterror = 1;
			continue;
		}

		cp = line + 6;
		while (isspace((unsigned char)*cp))
			cp++;

		while(*cp) {
			obj = cp;
			while (*cp && !isspace((unsigned char)*cp))
				cp++;
			if (*cp)
				*cp++ = '\0';
			add_string(&p->objs, obj);
			while (isspace((unsigned char)*cp))
				cp++;
		}
	}

	if ((rc=pclose(f)) != 0) {
		warnx("make error: make returned %d", rc);
		goterror = 1;
	}

	unlink(tempfname);
}