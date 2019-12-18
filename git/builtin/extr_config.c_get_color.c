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
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ color_parse (char const*,char*) ; 
 int /*<<< orphan*/  config_options ; 
 int /*<<< orphan*/  config_with_options (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_color_found ; 
 char const* get_color_slot ; 
 int /*<<< orphan*/  git_get_color_config ; 
 int /*<<< orphan*/  given_config_source ; 
 char* parsed_color ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void get_color(const char *var, const char *def_color)
{
	get_color_slot = var;
	get_color_found = 0;
	parsed_color[0] = '\0';
	config_with_options(git_get_color_config, NULL,
			    &given_config_source, &config_options);

	if (!get_color_found && def_color) {
		if (color_parse(def_color, parsed_color) < 0)
			die(_("unable to parse default color value"));
	}

	fputs(parsed_color, stdout);
}