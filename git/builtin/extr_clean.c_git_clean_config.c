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
 int LOOKUP_CONFIG (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * clean_colors ; 
 int /*<<< orphan*/  clean_use_color ; 
 int /*<<< orphan*/  colopts ; 
 int /*<<< orphan*/  color_interactive_slots ; 
 int color_parse (char const*,int /*<<< orphan*/ ) ; 
 int config_error_nonbool (char const*) ; 
 int force ; 
 int git_color_default_config (char const*,char const*,void*) ; 
 int git_column_config (char const*,char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  git_config_colorbool (char const*,char const*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int git_clean_config(const char *var, const char *value, void *cb)
{
	const char *slot_name;

	if (starts_with(var, "column."))
		return git_column_config(var, value, "clean", &colopts);

	/* honors the color.interactive* config variables which also
	   applied in git-add--interactive and git-stash */
	if (!strcmp(var, "color.interactive")) {
		clean_use_color = git_config_colorbool(var, value);
		return 0;
	}
	if (skip_prefix(var, "color.interactive.", &slot_name)) {
		int slot = LOOKUP_CONFIG(color_interactive_slots, slot_name);
		if (slot < 0)
			return 0;
		if (!value)
			return config_error_nonbool(var);
		return color_parse(value, clean_colors[slot]);
	}

	if (!strcmp(var, "clean.requireforce")) {
		force = !git_config_bool(var, value);
		return 0;
	}

	/* inspect the color.ui config variable and others */
	return git_color_default_config(var, value, cb);
}