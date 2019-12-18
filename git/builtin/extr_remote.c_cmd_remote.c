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

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_END () ; 
 struct option OPT__VERBOSE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OPT_STOP_AT_NON_OPTION ; 
 int /*<<< orphan*/  _ (char*) ; 
 int add (int,char const**) ; 
 int /*<<< orphan*/  builtin_remote_usage ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*) ; 
 int get_url (int,char const**) ; 
 int mv (int,char const**) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int prune (int,char const**) ; 
 int rm (int,char const**) ; 
 int set_branches (int,char const**) ; 
 int set_head (int,char const**) ; 
 int set_url (int,char const**) ; 
 int show (int,char const**) ; 
 int show_all () ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int update (int,char const**) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 
 int /*<<< orphan*/  verbose ; 

int cmd_remote(int argc, const char **argv, const char *prefix)
{
	struct option options[] = {
		OPT__VERBOSE(&verbose, N_("be verbose; must be placed before a subcommand")),
		OPT_END()
	};
	int result;

	argc = parse_options(argc, argv, prefix, options, builtin_remote_usage,
		PARSE_OPT_STOP_AT_NON_OPTION);

	if (argc < 1)
		result = show_all();
	else if (!strcmp(argv[0], "add"))
		result = add(argc, argv);
	else if (!strcmp(argv[0], "rename"))
		result = mv(argc, argv);
	else if (!strcmp(argv[0], "rm") || !strcmp(argv[0], "remove"))
		result = rm(argc, argv);
	else if (!strcmp(argv[0], "set-head"))
		result = set_head(argc, argv);
	else if (!strcmp(argv[0], "set-branches"))
		result = set_branches(argc, argv);
	else if (!strcmp(argv[0], "get-url"))
		result = get_url(argc, argv);
	else if (!strcmp(argv[0], "set-url"))
		result = set_url(argc, argv);
	else if (!strcmp(argv[0], "show"))
		result = show(argc, argv);
	else if (!strcmp(argv[0], "prune"))
		result = prune(argc, argv);
	else if (!strcmp(argv[0], "update"))
		result = update(argc, argv);
	else {
		error(_("Unknown subcommand: %s"), argv[0]);
		usage_with_options(builtin_remote_usage, options);
	}

	return result ? 1 : 0;
}