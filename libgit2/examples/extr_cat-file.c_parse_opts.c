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
struct opts {char* rev; int verbose; int /*<<< orphan*/  action; int /*<<< orphan*/  dir; } ;
struct args_info {int pos; } ;

/* Variables and functions */
 struct args_info ARGS_INFO_INIT ; 
 int /*<<< orphan*/  SHOW_NONE ; 
 int /*<<< orphan*/  SHOW_PRETTY ; 
 int /*<<< orphan*/  SHOW_SIZE ; 
 int /*<<< orphan*/  SHOW_TYPE ; 
 int /*<<< orphan*/  match_str_arg (int /*<<< orphan*/ *,struct args_info*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (char*,char*) ; 

__attribute__((used)) static void parse_opts(struct opts *o, int argc, char *argv[])
{
	struct args_info args = ARGS_INFO_INIT;

	for (args.pos = 1; args.pos < argc; ++args.pos) {
		char *a = argv[args.pos];

		if (a[0] != '-') {
			if (o->rev != NULL)
				usage("Only one rev should be provided", NULL);
			else
				o->rev = a;
		}
		else if (!strcmp(a, "-t"))
			o->action = SHOW_TYPE;
		else if (!strcmp(a, "-s"))
			o->action = SHOW_SIZE;
		else if (!strcmp(a, "-e"))
			o->action = SHOW_NONE;
		else if (!strcmp(a, "-p"))
			o->action = SHOW_PRETTY;
		else if (!strcmp(a, "-q"))
			o->verbose = 0;
		else if (!strcmp(a, "-v"))
			o->verbose = 1;
		else if (!strcmp(a, "--help") || !strcmp(a, "-h"))
			usage(NULL, NULL);
		else if (!match_str_arg(&o->dir, &args, "--git-dir"))
			usage("Unknown option", a);
	}

	if (!o->action || !o->rev)
		usage(NULL, NULL);

}