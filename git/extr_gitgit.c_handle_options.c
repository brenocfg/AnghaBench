#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {int nr; TYPE_1__* items; } ;
struct TYPE_2__ {char* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIR_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_GLOB_PATHSPECS_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_HTML_PATH ; 
 int /*<<< orphan*/  GIT_ICASE_PATHSPECS_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_IMPLICIT_WORK_TREE_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_INFO_PATH ; 
 int /*<<< orphan*/  GIT_LITERAL_PATHSPECS_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_MAN_PATH ; 
 int /*<<< orphan*/  GIT_NAMESPACE_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_NOGLOB_PATHSPECS_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_OPTIONAL_LOCKS_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_SUPER_PREFIX_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_WORK_TREE_ENVIRONMENT ; 
 int /*<<< orphan*/  NO_PARSEOPT ; 
 int /*<<< orphan*/  NO_REPLACE_OBJECTS_ENVIRONMENT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 char* _ (char*) ; 
 scalar_t__ chdir (char const*) ; 
 int /*<<< orphan*/  die_errno (char*,char const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_config_push_parameter (char const*) ; 
 int /*<<< orphan*/  git_exec_path () ; 
 int /*<<< orphan*/  git_set_exec_path (char const*) ; 
 int /*<<< orphan*/  git_usage_string ; 
 int is_bare_repository_cfg ; 
 int /*<<< orphan*/  list_builtins (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_cmds (char const*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 scalar_t__ read_replace_refs ; 
 int /*<<< orphan*/  set_alternate_shallow_file (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  setenv (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  trace2_cmd_name (char*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int use_pager ; 
 char* xgetcwd () ; 

__attribute__((used)) static int handle_options(const char ***argv, int *argc, int *envchanged)
{
	const char **orig_argv = *argv;

	while (*argc > 0) {
		const char *cmd = (*argv)[0];
		if (cmd[0] != '-')
			break;

		/*
		 * For legacy reasons, the "version" and "help"
		 * commands can be written with "--" prepended
		 * to make them look like flags.
		 */
		if (!strcmp(cmd, "--help") || !strcmp(cmd, "--version"))
			break;

		/*
		 * Check remaining flags.
		 */
		if (skip_prefix(cmd, "--exec-path", &cmd)) {
			if (*cmd == '=')
				git_set_exec_path(cmd + 1);
			else {
				puts(git_exec_path());
				trace2_cmd_name("_query_");
				exit(0);
			}
		} else if (!strcmp(cmd, "--html-path")) {
			puts(system_path(GIT_HTML_PATH));
			trace2_cmd_name("_query_");
			exit(0);
		} else if (!strcmp(cmd, "--man-path")) {
			puts(system_path(GIT_MAN_PATH));
			trace2_cmd_name("_query_");
			exit(0);
		} else if (!strcmp(cmd, "--info-path")) {
			puts(system_path(GIT_INFO_PATH));
			trace2_cmd_name("_query_");
			exit(0);
		} else if (!strcmp(cmd, "-p") || !strcmp(cmd, "--paginate")) {
			use_pager = 1;
		} else if (!strcmp(cmd, "-P") || !strcmp(cmd, "--no-pager")) {
			use_pager = 0;
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--no-replace-objects")) {
			read_replace_refs = 0;
			setenv(NO_REPLACE_OBJECTS_ENVIRONMENT, "1", 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--git-dir")) {
			if (*argc < 2) {
				fprintf(stderr, _("no directory given for --git-dir\n" ));
				usage(git_usage_string);
			}
			setenv(GIT_DIR_ENVIRONMENT, (*argv)[1], 1);
			if (envchanged)
				*envchanged = 1;
			(*argv)++;
			(*argc)--;
		} else if (skip_prefix(cmd, "--git-dir=", &cmd)) {
			setenv(GIT_DIR_ENVIRONMENT, cmd, 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--namespace")) {
			if (*argc < 2) {
				fprintf(stderr, _("no namespace given for --namespace\n" ));
				usage(git_usage_string);
			}
			setenv(GIT_NAMESPACE_ENVIRONMENT, (*argv)[1], 1);
			if (envchanged)
				*envchanged = 1;
			(*argv)++;
			(*argc)--;
		} else if (skip_prefix(cmd, "--namespace=", &cmd)) {
			setenv(GIT_NAMESPACE_ENVIRONMENT, cmd, 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--work-tree")) {
			if (*argc < 2) {
				fprintf(stderr, _("no directory given for --work-tree\n" ));
				usage(git_usage_string);
			}
			setenv(GIT_WORK_TREE_ENVIRONMENT, (*argv)[1], 1);
			if (envchanged)
				*envchanged = 1;
			(*argv)++;
			(*argc)--;
		} else if (skip_prefix(cmd, "--work-tree=", &cmd)) {
			setenv(GIT_WORK_TREE_ENVIRONMENT, cmd, 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--super-prefix")) {
			if (*argc < 2) {
				fprintf(stderr, _("no prefix given for --super-prefix\n" ));
				usage(git_usage_string);
			}
			setenv(GIT_SUPER_PREFIX_ENVIRONMENT, (*argv)[1], 1);
			if (envchanged)
				*envchanged = 1;
			(*argv)++;
			(*argc)--;
		} else if (skip_prefix(cmd, "--super-prefix=", &cmd)) {
			setenv(GIT_SUPER_PREFIX_ENVIRONMENT, cmd, 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--bare")) {
			char *cwd = xgetcwd();
			is_bare_repository_cfg = 1;
			setenv(GIT_DIR_ENVIRONMENT, cwd, 0);
			free(cwd);
			setenv(GIT_IMPLICIT_WORK_TREE_ENVIRONMENT, "0", 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "-c")) {
			if (*argc < 2) {
				fprintf(stderr, _("-c expects a configuration string\n" ));
				usage(git_usage_string);
			}
			git_config_push_parameter((*argv)[1]);
			(*argv)++;
			(*argc)--;
		} else if (!strcmp(cmd, "--literal-pathspecs")) {
			setenv(GIT_LITERAL_PATHSPECS_ENVIRONMENT, "1", 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--no-literal-pathspecs")) {
			setenv(GIT_LITERAL_PATHSPECS_ENVIRONMENT, "0", 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--glob-pathspecs")) {
			setenv(GIT_GLOB_PATHSPECS_ENVIRONMENT, "1", 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--noglob-pathspecs")) {
			setenv(GIT_NOGLOB_PATHSPECS_ENVIRONMENT, "1", 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--icase-pathspecs")) {
			setenv(GIT_ICASE_PATHSPECS_ENVIRONMENT, "1", 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--no-optional-locks")) {
			setenv(GIT_OPTIONAL_LOCKS_ENVIRONMENT, "0", 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--shallow-file")) {
			(*argv)++;
			(*argc)--;
			set_alternate_shallow_file(the_repository, (*argv)[0], 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "-C")) {
			if (*argc < 2) {
				fprintf(stderr, _("no directory given for -C\n" ));
				usage(git_usage_string);
			}
			if ((*argv)[1][0]) {
				if (chdir((*argv)[1]))
					die_errno("cannot change to '%s'", (*argv)[1]);
				if (envchanged)
					*envchanged = 1;
			}
			(*argv)++;
			(*argc)--;
		} else if (skip_prefix(cmd, "--list-cmds=", &cmd)) {
			trace2_cmd_name("_query_");
			if (!strcmp(cmd, "parseopt")) {
				struct string_list list = STRING_LIST_INIT_DUP;
				int i;

				list_builtins(&list, NO_PARSEOPT);
				for (i = 0; i < list.nr; i++)
					printf("%s ", list.items[i].string);
				string_list_clear(&list, 0);
				exit(0);
			} else {
				exit(list_cmds(cmd));
			}
		} else {
			fprintf(stderr, _("unknown option: %s\n"), cmd);
			usage(git_usage_string);
		}

		(*argv)++;
		(*argc)--;
	}
	return (*argv) - orig_argv;
}