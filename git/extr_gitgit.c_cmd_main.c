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

/* Variables and functions */
 scalar_t__ ENOENT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  commit_pager_choice () ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 char* find_last_dir_sep (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 char* git_more_info_string ; 
 char* git_usage_string ; 
 int /*<<< orphan*/  handle_builtin (int,char const**) ; 
 int /*<<< orphan*/  handle_options (char const***,int*,int /*<<< orphan*/ *) ; 
 char* help_unknown_cmd (char const*) ; 
 int /*<<< orphan*/  list_common_cmds_help () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int run_argv (int*,char const***) ; 
 int /*<<< orphan*/  setup_path () ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  trace_command_performance (char const**) ; 

int cmd_main(int argc, const char **argv)
{
	const char *cmd;
	int done_help = 0;

	cmd = argv[0];
	if (!cmd)
		cmd = "git-help";
	else {
		const char *slash = find_last_dir_sep(cmd);
		if (slash)
			cmd = slash + 1;
	}

	trace_command_performance(argv);

	/*
	 * "git-xxxx" is the same as "git xxxx", but we obviously:
	 *
	 *  - cannot take flags in between the "git" and the "xxxx".
	 *  - cannot execute it externally (since it would just do
	 *    the same thing over again)
	 *
	 * So we just directly call the builtin handler, and die if
	 * that one cannot handle it.
	 */
	if (skip_prefix(cmd, "git-", &cmd)) {
		argv[0] = cmd;
		handle_builtin(argc, argv);
		die(_("cannot handle %s as a builtin"), cmd);
	}

	/* Look for flags.. */
	argv++;
	argc--;
	handle_options(&argv, &argc, NULL);
	if (argc > 0) {
		/* translate --help and --version into commands */
		skip_prefix(argv[0], "--", &argv[0]);
	} else {
		/* The user didn't specify a command; give them help */
		commit_pager_choice();
		printf(_("usage: %s\n\n"), git_usage_string);
		list_common_cmds_help();
		printf("\n%s\n", _(git_more_info_string));
		exit(1);
	}
	cmd = argv[0];

	/*
	 * We use PATH to find git commands, but we prepend some higher
	 * precedence paths: the "--exec-path" option, the GIT_EXEC_PATH
	 * environment, and the $(gitexecdir) from the Makefile at build
	 * time.
	 */
	setup_path();

	while (1) {
		int was_alias = run_argv(&argc, &argv);
		if (errno != ENOENT)
			break;
		if (was_alias) {
			fprintf(stderr, _("expansion of alias '%s' failed; "
					  "'%s' is not a git command\n"),
				cmd, argv[0]);
			exit(1);
		}
		if (!done_help) {
			cmd = argv[0] = help_unknown_cmd(cmd);
			done_help = 1;
		} else
			break;
	}

	fprintf(stderr, _("failed to run command '%s': %s\n"),
		cmd, strerror(errno));

	return 1;
}