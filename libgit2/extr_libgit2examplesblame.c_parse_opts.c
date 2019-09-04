#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct opts {int M; int C; int F; char* commitspec; char* path; int /*<<< orphan*/  end_line; int /*<<< orphan*/  start_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_lg2 (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ sscanf (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void parse_opts(struct opts *o, int argc, char *argv[])
{
	int i;
	char *bare_args[3] = {0};

	if (argc < 2) usage(NULL, NULL);

	for (i=1; i<argc; i++) {
		char *a = argv[i];

		if (a[0] != '-') {
			int i=0;
			while (bare_args[i] && i < 3) ++i;
			if (i >= 3)
				usage("Invalid argument set", NULL);
			bare_args[i] = a;
		}
		else if (!strcmp(a, "--"))
			continue;
		else if (!strcasecmp(a, "-M"))
			o->M = 1;
		else if (!strcasecmp(a, "-C"))
			o->C = 1;
		else if (!strcasecmp(a, "-F"))
			o->F = 1;
		else if (!strcasecmp(a, "-L")) {
			i++; a = argv[i];
			if (i >= argc) fatal("Not enough arguments to -L", NULL);
			check_lg2(sscanf(a, "%d,%d", &o->start_line, &o->end_line)-2, "-L format error", NULL);
		}
		else {
			/* commit range */
			if (o->commitspec) fatal("Only one commit spec allowed", NULL);
			o->commitspec = a;
		}
	}

	/* Handle the bare arguments */
	if (!bare_args[0]) usage("Please specify a path", NULL);
	o->path = bare_args[0];
	if (bare_args[1]) {
		/* <commitspec> <path> */
		o->path = bare_args[1];
		o->commitspec = bare_args[0];
	}
	if (bare_args[2]) {
		/* <oldcommit> <newcommit> <path> */
		char spec[128] = {0};
		o->path = bare_args[2];
		sprintf(spec, "%s..%s", bare_args[0], bare_args[1]);
		o->commitspec = spec;
	}
}