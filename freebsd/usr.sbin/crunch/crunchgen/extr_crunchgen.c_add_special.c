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
struct TYPE_3__ {int /*<<< orphan*/ * libs; int /*<<< orphan*/ * buildopts; int /*<<< orphan*/ * objvar; int /*<<< orphan*/ * keeplist; int /*<<< orphan*/ * objpaths; int /*<<< orphan*/ * objs; int /*<<< orphan*/ * objdir; int /*<<< orphan*/ * srcdir; int /*<<< orphan*/ * ident; } ;
typedef  TYPE_1__ prog_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_string (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  curfilename ; 
 TYPE_1__* find_prog (char*) ; 
 int goterror ; 
 int /*<<< orphan*/  linenum ; 
 int /*<<< orphan*/  out_of_memory () ; 
 scalar_t__ reading_cache ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

void
add_special(int argc, char **argv)
{
	int i;
	prog_t *p = find_prog(argv[1]);

	if (p == NULL) {
		if (reading_cache)
			return;

		warnx("%s:%d: no prog %s previously declared, skipping special",
		    curfilename, linenum, argv[1]);
		goterror = 1;
		return;
	}

	if (!strcmp(argv[2], "ident")) {
		if (argc != 4)
			goto argcount;
		if ((p->ident = strdup(argv[3])) == NULL)
			out_of_memory();
	} else if (!strcmp(argv[2], "srcdir")) {
		if (argc != 4)
			goto argcount;
		if ((p->srcdir = strdup(argv[3])) == NULL)
			out_of_memory();
	} else if (!strcmp(argv[2], "objdir")) {
		if(argc != 4)
			goto argcount;
		if((p->objdir = strdup(argv[3])) == NULL)
			out_of_memory();
	} else if (!strcmp(argv[2], "objs")) {
		p->objs = NULL;
		for (i = 3; i < argc; i++)
			add_string(&p->objs, argv[i]);
	} else if (!strcmp(argv[2], "objpaths")) {
		p->objpaths = NULL;
		for (i = 3; i < argc; i++)
			add_string(&p->objpaths, argv[i]);
	} else if (!strcmp(argv[2], "keep")) {
		p->keeplist = NULL;
		for(i = 3; i < argc; i++)
			add_string(&p->keeplist, argv[i]);
	} else if (!strcmp(argv[2], "objvar")) {
		if(argc != 4)
			goto argcount;
		if ((p->objvar = strdup(argv[3])) == NULL)
			out_of_memory();
	} else if (!strcmp(argv[2], "buildopts")) {
		p->buildopts = NULL;
		for (i = 3; i < argc; i++)
			add_string(&p->buildopts, argv[i]);
	} else if (!strcmp(argv[2], "lib")) {
		for (i = 3; i < argc; i++)
			add_string(&p->libs, argv[i]);
	} else {
		warnx("%s:%d: bad parameter name `%s', skipping line",
		    curfilename, linenum, argv[2]);
		goterror = 1;
	}
	return;

 argcount:
	warnx("%s:%d: too %s arguments, expected \"special %s %s <string>\"",
	    curfilename, linenum, argc < 4? "few" : "many", argv[1], argv[2]);
	goterror = 1;
}