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
 int /*<<< orphan*/  git_config_colorbool (char const*,char const*) ; 
 int /*<<< orphan*/  git_use_color_default ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int git_color_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "color.ui")) {
		git_use_color_default = git_config_colorbool(var, value);
		return 0;
	}

	return 0;
}