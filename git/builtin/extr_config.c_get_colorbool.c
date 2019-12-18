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
 int GIT_COLOR_AUTO ; 
 int /*<<< orphan*/  config_options ; 
 int /*<<< orphan*/  config_with_options (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_color_ui_found ; 
 int get_colorbool_found ; 
 char const* get_colorbool_slot ; 
 int get_diff_color_found ; 
 int /*<<< orphan*/  git_get_colorbool_config ; 
 int /*<<< orphan*/  given_config_source ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int want_color (int) ; 

__attribute__((used)) static int get_colorbool(const char *var, int print)
{
	get_colorbool_slot = var;
	get_colorbool_found = -1;
	get_diff_color_found = -1;
	get_color_ui_found = -1;
	config_with_options(git_get_colorbool_config, NULL,
			    &given_config_source, &config_options);

	if (get_colorbool_found < 0) {
		if (!strcmp(get_colorbool_slot, "color.diff"))
			get_colorbool_found = get_diff_color_found;
		if (get_colorbool_found < 0)
			get_colorbool_found = get_color_ui_found;
	}

	if (get_colorbool_found < 0)
		/* default value if none found in config */
		get_colorbool_found = GIT_COLOR_AUTO;

	get_colorbool_found = want_color(get_colorbool_found);

	if (print) {
		printf("%s\n", get_colorbool_found ? "true" : "false");
		return 0;
	} else
		return get_colorbool_found ? 0 : 1;
}