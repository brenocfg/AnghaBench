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
 int /*<<< orphan*/  add_man_viewer (char const*) ; 
 int add_man_viewer_info (char const*,char const*) ; 
 int /*<<< orphan*/  colopts ; 
 int config_error_nonbool (char const*) ; 
 int git_column_config (char const*,char const*,char*,int /*<<< orphan*/ *) ; 
 int git_default_config (char const*,char const*,void*) ; 
 int /*<<< orphan*/  help_format ; 
 int /*<<< orphan*/  html_path ; 
 int /*<<< orphan*/  parse_help_format (char const*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int git_help_config(const char *var, const char *value, void *cb)
{
	if (starts_with(var, "column."))
		return git_column_config(var, value, "help", &colopts);
	if (!strcmp(var, "help.format")) {
		if (!value)
			return config_error_nonbool(var);
		help_format = parse_help_format(value);
		return 0;
	}
	if (!strcmp(var, "help.htmlpath")) {
		if (!value)
			return config_error_nonbool(var);
		html_path = xstrdup(value);
		return 0;
	}
	if (!strcmp(var, "man.viewer")) {
		if (!value)
			return config_error_nonbool(var);
		add_man_viewer(value);
		return 0;
	}
	if (starts_with(var, "man."))
		return add_man_viewer_info(var, value);

	return git_default_config(var, value, cb);
}