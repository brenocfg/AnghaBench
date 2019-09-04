#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct worktree {int dummy; } ;
struct TYPE_8__ {int respect_includes; int /*<<< orphan*/  git_dir; int /*<<< orphan*/  commondir; } ;
struct TYPE_7__ {char* file; int use_stdin; scalar_t__ blob; } ;
struct TYPE_6__ {int /*<<< orphan*/  have_repository; } ;

/* Variables and functions */
 int ACTION_ADD ; 
 int ACTION_EDIT ; 
 int ACTION_GET ; 
 int ACTION_GET_ALL ; 
 int ACTION_GET_COLOR ; 
 int ACTION_GET_COLORBOOL ; 
 int ACTION_GET_REGEXP ; 
 int ACTION_GET_URLMATCH ; 
 int ACTION_LIST ; 
 int ACTION_REMOVE_SECTION ; 
 int ACTION_RENAME_SECTION ; 
 int ACTION_REPLACE_ALL ; 
 int ACTION_SET ; 
 int ACTION_SET_ALL ; 
 int ACTION_UNSET ; 
 int ACTION_UNSET_ALL ; 
 int /*<<< orphan*/  CONFIG_ENVIRONMENT ; 
 int CONFIG_NOTHING_SET ; 
 char const* CONFIG_REGEX_NONE ; 
 scalar_t__ EEXIST ; 
 scalar_t__ HAS_MULTI_BITS (int) ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int PAGING_ACTIONS ; 
 int /*<<< orphan*/  PARSE_OPT_STOP_AT_NON_OPTION ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  UNLEAK (char*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ access_or_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int actions ; 
 int /*<<< orphan*/  builtin_config_options ; 
 int /*<<< orphan*/  builtin_config_usage ; 
 int /*<<< orphan*/  check_argc (int,int,int) ; 
 int /*<<< orphan*/  check_write () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  color_stdout_is_tty ; 
 TYPE_4__ config_options ; 
 scalar_t__ config_with_options (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,TYPE_4__*) ; 
 char* default_user_config () ; 
 scalar_t__ default_value ; 
 char delim ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char*) ; 
 int do_all ; 
 scalar_t__ end_null ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,...) ; 
 char* expand_user_path (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_worktrees (struct worktree**) ; 
 int /*<<< orphan*/  get_color (char const*,char const*) ; 
 int get_colorbool (char const*,int) ; 
 int /*<<< orphan*/  get_git_common_dir () ; 
 int /*<<< orphan*/  get_git_dir () ; 
 int get_urlmatch (char const*,char const*) ; 
 int get_value (char const*,char const*) ; 
 struct worktree** get_worktrees (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_bool (char*,char const*) ; 
 int git_config_rename_section_in_file (char*,char const*,char const*) ; 
 int git_config_set_in_file_gently (char*,char const*,char*) ; 
 int git_config_set_multivar_in_file_gently (char*,char const*,char*,char const*,int) ; 
 int /*<<< orphan*/  git_default_config ; 
 char* git_etc_gitconfig () ; 
 void* git_pathdup (char*) ; 
 TYPE_2__ given_config_source ; 
 int /*<<< orphan*/  is_absolute_path (char*) ; 
 char key_delim ; 
 int /*<<< orphan*/  launch_editor (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* normalize_value (char const*,char const*) ; 
 scalar_t__ omit_values ; 
 int open (char*,int,int) ; 
 int parse_options (int,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* prefix_filename (char const*,char*) ; 
 scalar_t__ repository_format_worktree_config ; 
 int respect_includes_opt ; 
 int /*<<< orphan*/  setup_auto_pager (char*,int) ; 
 int /*<<< orphan*/  show_all_config ; 
 int show_keys ; 
 scalar_t__ show_origin ; 
 TYPE_1__* startup_info ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char term ; 
 scalar_t__ type ; 
 int /*<<< orphan*/  usage_builtin_config () ; 
 int use_global_config ; 
 int use_key_regexp ; 
 int use_local_config ; 
 int use_system_config ; 
 int use_worktree_config ; 
 int /*<<< orphan*/  write_str_in_full (int,char*) ; 
 char* xdg_config_home (char*) ; 
 void* xstrdup (char*) ; 
 char* xstrdup_or_null (int /*<<< orphan*/ ) ; 

int cmd_config(int argc, const char **argv, const char *prefix)
{
	int nongit = !startup_info->have_repository;
	char *value;

	given_config_source.file = xstrdup_or_null(getenv(CONFIG_ENVIRONMENT));

	argc = parse_options(argc, argv, prefix, builtin_config_options,
			     builtin_config_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	if (use_global_config + use_system_config + use_local_config +
	    use_worktree_config +
	    !!given_config_source.file + !!given_config_source.blob > 1) {
		error(_("only one config file at a time"));
		usage_builtin_config();
	}

	if (use_local_config && nongit)
		die(_("--local can only be used inside a git repository"));

	if (given_config_source.blob && nongit)
		die(_("--blob can only be used inside a git repository"));

	if (given_config_source.file &&
			!strcmp(given_config_source.file, "-")) {
		given_config_source.file = NULL;
		given_config_source.use_stdin = 1;
	}

	if (use_global_config) {
		char *user_config = expand_user_path("~/.gitconfig", 0);
		char *xdg_config = xdg_config_home("config");

		if (!user_config)
			/*
			 * It is unknown if HOME/.gitconfig exists, so
			 * we do not know if we should write to XDG
			 * location; error out even if XDG_CONFIG_HOME
			 * is set and points at a sane location.
			 */
			die(_("$HOME not set"));

		if (access_or_warn(user_config, R_OK, 0) &&
		    xdg_config && !access_or_warn(xdg_config, R_OK, 0)) {
			given_config_source.file = xdg_config;
			free(user_config);
		} else {
			given_config_source.file = user_config;
			free(xdg_config);
		}
	}
	else if (use_system_config)
		given_config_source.file = git_etc_gitconfig();
	else if (use_local_config)
		given_config_source.file = git_pathdup("config");
	else if (use_worktree_config) {
		struct worktree **worktrees = get_worktrees(0);
		if (repository_format_worktree_config)
			given_config_source.file = git_pathdup("config.worktree");
		else if (worktrees[0] && worktrees[1])
			die(_("--worktree cannot be used with multiple "
			      "working trees unless the config\n"
			      "extension worktreeConfig is enabled. "
			      "Please read \"CONFIGURATION FILE\"\n"
			      "section in \"git help worktree\" for details"));
		else
			given_config_source.file = git_pathdup("config");
		free_worktrees(worktrees);
	} else if (given_config_source.file) {
		if (!is_absolute_path(given_config_source.file) && prefix)
			given_config_source.file =
				prefix_filename(prefix, given_config_source.file);
	}

	if (respect_includes_opt == -1)
		config_options.respect_includes = !given_config_source.file;
	else
		config_options.respect_includes = respect_includes_opt;
	if (!nongit) {
		config_options.commondir = get_git_common_dir();
		config_options.git_dir = get_git_dir();
	}

	if (end_null) {
		term = '\0';
		delim = '\n';
		key_delim = '\n';
	}

	if ((actions & (ACTION_GET_COLOR|ACTION_GET_COLORBOOL)) && type) {
		error(_("--get-color and variable type are incoherent"));
		usage_builtin_config();
	}

	if (HAS_MULTI_BITS(actions)) {
		error(_("only one action at a time"));
		usage_builtin_config();
	}
	if (actions == 0)
		switch (argc) {
		case 1: actions = ACTION_GET; break;
		case 2: actions = ACTION_SET; break;
		case 3: actions = ACTION_SET_ALL; break;
		default:
			usage_builtin_config();
		}
	if (omit_values &&
	    !(actions == ACTION_LIST || actions == ACTION_GET_REGEXP)) {
		error(_("--name-only is only applicable to --list or --get-regexp"));
		usage_builtin_config();
	}

	if (show_origin && !(actions &
		(ACTION_GET|ACTION_GET_ALL|ACTION_GET_REGEXP|ACTION_LIST))) {
		error(_("--show-origin is only applicable to --get, --get-all, "
			"--get-regexp, and --list"));
		usage_builtin_config();
	}

	if (default_value && !(actions & ACTION_GET)) {
		error(_("--default is only applicable to --get"));
		usage_builtin_config();
	}

	if (actions & PAGING_ACTIONS)
		setup_auto_pager("config", 1);

	if (actions == ACTION_LIST) {
		check_argc(argc, 0, 0);
		if (config_with_options(show_all_config, NULL,
					&given_config_source,
					&config_options) < 0) {
			if (given_config_source.file)
				die_errno(_("unable to read config file '%s'"),
					  given_config_source.file);
			else
				die(_("error processing config file(s)"));
		}
	}
	else if (actions == ACTION_EDIT) {
		char *config_file;

		check_argc(argc, 0, 0);
		if (!given_config_source.file && nongit)
			die(_("not in a git directory"));
		if (given_config_source.use_stdin)
			die(_("editing stdin is not supported"));
		if (given_config_source.blob)
			die(_("editing blobs is not supported"));
		git_config(git_default_config, NULL);
		config_file = given_config_source.file ?
				xstrdup(given_config_source.file) :
				git_pathdup("config");
		if (use_global_config) {
			int fd = open(config_file, O_CREAT | O_EXCL | O_WRONLY, 0666);
			if (fd >= 0) {
				char *content = default_user_config();
				write_str_in_full(fd, content);
				free(content);
				close(fd);
			}
			else if (errno != EEXIST)
				die_errno(_("cannot create configuration file %s"), config_file);
		}
		launch_editor(config_file, NULL, NULL);
		free(config_file);
	}
	else if (actions == ACTION_SET) {
		int ret;
		check_write();
		check_argc(argc, 2, 2);
		value = normalize_value(argv[0], argv[1]);
		UNLEAK(value);
		ret = git_config_set_in_file_gently(given_config_source.file, argv[0], value);
		if (ret == CONFIG_NOTHING_SET)
			error(_("cannot overwrite multiple values with a single value\n"
			"       Use a regexp, --add or --replace-all to change %s."), argv[0]);
		return ret;
	}
	else if (actions == ACTION_SET_ALL) {
		check_write();
		check_argc(argc, 2, 3);
		value = normalize_value(argv[0], argv[1]);
		UNLEAK(value);
		return git_config_set_multivar_in_file_gently(given_config_source.file,
							      argv[0], value, argv[2], 0);
	}
	else if (actions == ACTION_ADD) {
		check_write();
		check_argc(argc, 2, 2);
		value = normalize_value(argv[0], argv[1]);
		UNLEAK(value);
		return git_config_set_multivar_in_file_gently(given_config_source.file,
							      argv[0], value,
							      CONFIG_REGEX_NONE, 0);
	}
	else if (actions == ACTION_REPLACE_ALL) {
		check_write();
		check_argc(argc, 2, 3);
		value = normalize_value(argv[0], argv[1]);
		UNLEAK(value);
		return git_config_set_multivar_in_file_gently(given_config_source.file,
							      argv[0], value, argv[2], 1);
	}
	else if (actions == ACTION_GET) {
		check_argc(argc, 1, 2);
		return get_value(argv[0], argv[1]);
	}
	else if (actions == ACTION_GET_ALL) {
		do_all = 1;
		check_argc(argc, 1, 2);
		return get_value(argv[0], argv[1]);
	}
	else if (actions == ACTION_GET_REGEXP) {
		show_keys = 1;
		use_key_regexp = 1;
		do_all = 1;
		check_argc(argc, 1, 2);
		return get_value(argv[0], argv[1]);
	}
	else if (actions == ACTION_GET_URLMATCH) {
		check_argc(argc, 2, 2);
		return get_urlmatch(argv[0], argv[1]);
	}
	else if (actions == ACTION_UNSET) {
		check_write();
		check_argc(argc, 1, 2);
		if (argc == 2)
			return git_config_set_multivar_in_file_gently(given_config_source.file,
								      argv[0], NULL, argv[1], 0);
		else
			return git_config_set_in_file_gently(given_config_source.file,
							     argv[0], NULL);
	}
	else if (actions == ACTION_UNSET_ALL) {
		check_write();
		check_argc(argc, 1, 2);
		return git_config_set_multivar_in_file_gently(given_config_source.file,
							      argv[0], NULL, argv[1], 1);
	}
	else if (actions == ACTION_RENAME_SECTION) {
		int ret;
		check_write();
		check_argc(argc, 2, 2);
		ret = git_config_rename_section_in_file(given_config_source.file,
							argv[0], argv[1]);
		if (ret < 0)
			return ret;
		if (ret == 0)
			die(_("no such section: %s"), argv[0]);
	}
	else if (actions == ACTION_REMOVE_SECTION) {
		int ret;
		check_write();
		check_argc(argc, 1, 1);
		ret = git_config_rename_section_in_file(given_config_source.file,
							argv[0], NULL);
		if (ret < 0)
			return ret;
		if (ret == 0)
			die(_("no such section: %s"), argv[0]);
	}
	else if (actions == ACTION_GET_COLOR) {
		check_argc(argc, 1, 2);
		get_color(argv[0], argv[1]);
	}
	else if (actions == ACTION_GET_COLORBOOL) {
		check_argc(argc, 1, 2);
		if (argc == 2)
			color_stdout_is_tty = git_config_bool("command line", argv[1]);
		return get_colorbool(argv[0], argc == 2);
	}

	return 0;
}