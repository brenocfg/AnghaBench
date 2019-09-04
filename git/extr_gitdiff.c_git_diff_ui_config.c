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
 unsigned int COLOR_MOVED_WS_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  default_diff_options ; 
 scalar_t__ diff_algorithm ; 
 void* diff_auto_refresh_index ; 
 int diff_color_moved_default ; 
 unsigned int diff_color_moved_ws_default ; 
 scalar_t__ diff_context_default ; 
 int /*<<< orphan*/  diff_detect_rename_default ; 
 scalar_t__ diff_interhunk_context_default ; 
 void* diff_mnemonic_prefix ; 
 void* diff_no_prefix ; 
 int /*<<< orphan*/  diff_order_file_cfg ; 
 void* diff_stat_graph_width ; 
 int /*<<< orphan*/  diff_use_color_default ; 
 int /*<<< orphan*/  diff_word_regex_cfg ; 
 int /*<<< orphan*/  external_diff_cmd_cfg ; 
 scalar_t__ git_color_config (char const*,char const*,void*) ; 
 void* git_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  git_config_colorbool (char const*,char const*) ; 
 void* git_config_int (char const*,char const*) ; 
 int git_config_pathname (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  git_config_rename (char const*,char const*) ; 
 int git_config_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int git_diff_basic_config (char const*,char const*,void*) ; 
 int /*<<< orphan*/  handle_ignore_submodules_arg (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ parse_algorithm_value (char const*) ; 
 int parse_color_moved (char const*) ; 
 unsigned int parse_color_moved_ws (char const*) ; 
 scalar_t__ parse_submodule_params (int /*<<< orphan*/ *,char const*) ; 
 int parse_ws_error_highlight (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*) ; 
 int ws_error_highlight_default ; 

int git_diff_ui_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "diff.color") || !strcmp(var, "color.diff")) {
		diff_use_color_default = git_config_colorbool(var, value);
		return 0;
	}
	if (!strcmp(var, "diff.colormoved")) {
		int cm = parse_color_moved(value);
		if (cm < 0)
			return -1;
		diff_color_moved_default = cm;
		return 0;
	}
	if (!strcmp(var, "diff.colormovedws")) {
		unsigned cm = parse_color_moved_ws(value);
		if (cm & COLOR_MOVED_WS_ERROR)
			return -1;
		diff_color_moved_ws_default = cm;
		return 0;
	}
	if (!strcmp(var, "diff.context")) {
		diff_context_default = git_config_int(var, value);
		if (diff_context_default < 0)
			return -1;
		return 0;
	}
	if (!strcmp(var, "diff.interhunkcontext")) {
		diff_interhunk_context_default = git_config_int(var, value);
		if (diff_interhunk_context_default < 0)
			return -1;
		return 0;
	}
	if (!strcmp(var, "diff.renames")) {
		diff_detect_rename_default = git_config_rename(var, value);
		return 0;
	}
	if (!strcmp(var, "diff.autorefreshindex")) {
		diff_auto_refresh_index = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "diff.mnemonicprefix")) {
		diff_mnemonic_prefix = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "diff.noprefix")) {
		diff_no_prefix = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "diff.statgraphwidth")) {
		diff_stat_graph_width = git_config_int(var, value);
		return 0;
	}
	if (!strcmp(var, "diff.external"))
		return git_config_string(&external_diff_cmd_cfg, var, value);
	if (!strcmp(var, "diff.wordregex"))
		return git_config_string(&diff_word_regex_cfg, var, value);
	if (!strcmp(var, "diff.orderfile"))
		return git_config_pathname(&diff_order_file_cfg, var, value);

	if (!strcmp(var, "diff.ignoresubmodules"))
		handle_ignore_submodules_arg(&default_diff_options, value);

	if (!strcmp(var, "diff.submodule")) {
		if (parse_submodule_params(&default_diff_options, value))
			warning(_("Unknown value for 'diff.submodule' config variable: '%s'"),
				value);
		return 0;
	}

	if (!strcmp(var, "diff.algorithm")) {
		diff_algorithm = parse_algorithm_value(value);
		if (diff_algorithm < 0)
			return -1;
		return 0;
	}

	if (!strcmp(var, "diff.wserrorhighlight")) {
		int val = parse_ws_error_highlight(value);
		if (val < 0)
			return -1;
		ws_error_highlight_default = val;
		return 0;
	}

	if (git_color_config(var, value, cb) < 0)
		return -1;

	return git_diff_basic_config(var, value, cb);
}