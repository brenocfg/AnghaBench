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
struct option {int dummy; } ;
struct argv_array {int argc; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BOOL (char,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 int /*<<< orphan*/  PARSE_OPT_KEEP_ARGV0 ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_pop (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char const*) ; 
 int /*<<< orphan*/  builtin_remote_update_usage ; 
 int /*<<< orphan*/  get_remote_default ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int*) ; 
 int parse_options (int,char const**,int /*<<< orphan*/ *,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int run_command_v_opt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int update(int argc, const char **argv)
{
	int i, prune = -1;
	struct option options[] = {
		OPT_BOOL('p', "prune", &prune,
			 N_("prune remotes after fetching")),
		OPT_END()
	};
	struct argv_array fetch_argv = ARGV_ARRAY_INIT;
	int default_defined = 0;
	int retval;

	argc = parse_options(argc, argv, NULL, options, builtin_remote_update_usage,
			     PARSE_OPT_KEEP_ARGV0);

	argv_array_push(&fetch_argv, "fetch");

	if (prune != -1)
		argv_array_push(&fetch_argv, prune ? "--prune" : "--no-prune");
	if (verbose)
		argv_array_push(&fetch_argv, "-v");
	argv_array_push(&fetch_argv, "--multiple");
	if (argc < 2)
		argv_array_push(&fetch_argv, "default");
	for (i = 1; i < argc; i++)
		argv_array_push(&fetch_argv, argv[i]);

	if (strcmp(fetch_argv.argv[fetch_argv.argc-1], "default") == 0) {
		git_config(get_remote_default, &default_defined);
		if (!default_defined) {
			argv_array_pop(&fetch_argv);
			argv_array_push(&fetch_argv, "--all");
		}
	}

	retval = run_command_v_opt(fetch_argv.argv, RUN_GIT_CMD);
	argv_array_clear(&fetch_argv);
	return retval;
}