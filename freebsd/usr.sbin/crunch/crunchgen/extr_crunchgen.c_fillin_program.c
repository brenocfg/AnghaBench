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
struct TYPE_4__ {char* name; char* srcdir; char* realsrcdir; char* objdir; int goterror; int /*<<< orphan*/  objs; scalar_t__ ident; } ;
typedef  TYPE_1__ prog_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXLINELEN ; 
 int MAXPATHLEN ; 
 char* dir_search (char*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fillin_program_objs (TYPE_1__*,char*) ; 
 scalar_t__ genident (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  infilename ; 
 scalar_t__ is_dir (char*) ; 
 scalar_t__ is_nonempty_file (char*) ; 
 int /*<<< orphan*/  makeobj ; 
 char* objprefix ; 
 int /*<<< orphan*/  out_of_memory () ; 
 scalar_t__ pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  status (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* strdup (char*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  warnx (char*,char*,char*,...) ; 

void
fillin_program(prog_t *p)
{
	char path[MAXPATHLEN];
	char line[MAXLINELEN];
	FILE *f;

	snprintf(line, MAXLINELEN, "filling in parms for %s", p->name);
	status(line);

	if (!p->ident)
		p->ident = genident(p->name);

	/* look for the source directory if one wasn't specified by a special */
	if (!p->srcdir) {
		p->srcdir = dir_search(p->name);
	}

	/* Determine the actual srcdir (maybe symlinked). */
	if (p->srcdir) {
		snprintf(line, MAXLINELEN, "cd %s && echo -n `/bin/pwd`",
		    p->srcdir);
		f = popen(line,"r");
		if (!f)
			errx(1, "Can't execute: %s\n", line);

		path[0] = '\0';
		fgets(path, sizeof path, f);
		if (pclose(f))
			errx(1, "Can't execute: %s\n", line);

		if (!*path)
			errx(1, "Can't perform pwd on: %s\n", p->srcdir);

		p->realsrcdir = strdup(path);
	}

	/* Unless the option to make object files was specified the
	* the objects will be built in the source directory unless
	* an object directory already exists.
	*/
	if (!makeobj && !p->objdir && p->srcdir) {
		char *auto_obj;

		auto_obj = NULL;
		snprintf(line, sizeof line, "%s/%s", objprefix, p->realsrcdir);
		if (is_dir(line) ||
		    ((auto_obj = getenv("MK_AUTO_OBJ")) != NULL &&
		    strcmp(auto_obj, "yes") == 0)) {
			if ((p->objdir = strdup(line)) == NULL)
			out_of_memory();
		} else
			p->objdir = p->realsrcdir;
	}

	/*
	* XXX look for a Makefile.{name} in local directory first.
	* This lets us override the original Makefile.
	*/
	snprintf(path, sizeof(path), "Makefile.%s", p->name);
	if (is_nonempty_file(path)) {
		snprintf(line, MAXLINELEN, "Using %s for %s", path, p->name);
		status(line);
	} else
		if (p->srcdir)
			snprintf(path, sizeof(path), "%s/Makefile", p->srcdir);
	if (!p->objs && p->srcdir && is_nonempty_file(path))
		fillin_program_objs(p, path);

	if (!p->srcdir && !p->objdir && verbose)
		warnx("%s: %s: %s",
		    "warning: could not find source directory",
		    infilename, p->name);
	if (!p->objs && verbose)
		warnx("%s: %s: warning: could not find any .o files",
		    infilename, p->name);

	if ((!p->srcdir || !p->objdir) && !p->objs)
		p->goterror = 1;
}