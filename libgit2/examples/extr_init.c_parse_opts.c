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
struct opts {char* dir; int quiet; int bare; int initial_commit; char const* template; char const* gitdir; int /*<<< orphan*/  shared; scalar_t__ no_options; } ;
struct args_info {int pos; } ;

/* Variables and functions */
 struct args_info ARGS_INFO_INIT ; 
 int /*<<< orphan*/  GIT_REPOSITORY_INIT_SHARED_GROUP ; 
 scalar_t__ match_str_arg (char const**,struct args_info*,char*) ; 
 int /*<<< orphan*/  parse_shared (char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (char*,char*) ; 

__attribute__((used)) static void parse_opts(struct opts *o, int argc, char *argv[])
{
	struct args_info args = ARGS_INFO_INIT;
	const char *sharedarg;

	/** Process arguments. */

	for (args.pos = 1; args.pos < argc; ++args.pos) {
		char *a = argv[args.pos];

		if (a[0] == '-')
			o->no_options = 0;

		if (a[0] != '-') {
			if (o->dir != NULL)
				usage("extra argument", a);
			o->dir = a;
		}
		else if (!strcmp(a, "-q") || !strcmp(a, "--quiet"))
			o->quiet = 1;
		else if (!strcmp(a, "--bare"))
			o->bare = 1;
		else if (!strcmp(a, "--shared"))
			o->shared = GIT_REPOSITORY_INIT_SHARED_GROUP;
		else if (!strcmp(a, "--initial-commit"))
			o->initial_commit = 1;
		else if (match_str_arg(&sharedarg, &args, "--shared"))
			o->shared = parse_shared(sharedarg);
		else if (!match_str_arg(&o->template, &args, "--template") ||
		         !match_str_arg(&o->gitdir, &args, "--separate-git-dir"))
			usage("unknown option", a);
	}

	if (!o->dir)
		usage("must specify directory to init", "");
}