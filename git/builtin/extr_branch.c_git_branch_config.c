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
struct ref_sorting {int dummy; } ;

/* Variables and functions */
 int LOOKUP_CONFIG (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * branch_colors ; 
 int /*<<< orphan*/  branch_use_color ; 
 int /*<<< orphan*/  colopts ; 
 int /*<<< orphan*/  color_branch_slots ; 
 int color_parse (char const*,int /*<<< orphan*/ ) ; 
 int config_error_nonbool (char const*) ; 
 int git_color_default_config (char const*,char const*,void*) ; 
 int git_column_config (char const*,char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_colorbool (char const*,char const*) ; 
 int /*<<< orphan*/  parse_ref_sorting (struct ref_sorting**,char const*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int git_branch_config(const char *var, const char *value, void *cb)
{
	const char *slot_name;
	struct ref_sorting **sorting_tail = (struct ref_sorting **)cb;

	if (!strcmp(var, "branch.sort")) {
		if (!value)
			return config_error_nonbool(var);
		parse_ref_sorting(sorting_tail, value);
		return 0;
	}

	if (starts_with(var, "column."))
		return git_column_config(var, value, "branch", &colopts);
	if (!strcmp(var, "color.branch")) {
		branch_use_color = git_config_colorbool(var, value);
		return 0;
	}
	if (skip_prefix(var, "color.branch.", &slot_name)) {
		int slot = LOOKUP_CONFIG(color_branch_slots, slot_name);
		if (slot < 0)
			return 0;
		if (!value)
			return config_error_nonbool(var);
		return color_parse(value, branch_colors[slot]);
	}
	return git_color_default_config(var, value, cb);
}