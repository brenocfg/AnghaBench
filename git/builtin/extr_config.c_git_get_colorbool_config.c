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
 void* get_color_ui_found ; 
 void* get_colorbool_found ; 
 char* get_colorbool_slot ; 
 void* get_diff_color_found ; 
 void* git_config_colorbool (char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int git_get_colorbool_config(const char *var, const char *value,
		void *cb)
{
	if (!strcmp(var, get_colorbool_slot))
		get_colorbool_found = git_config_colorbool(var, value);
	else if (!strcmp(var, "diff.color"))
		get_diff_color_found = git_config_colorbool(var, value);
	else if (!strcmp(var, "color.ui"))
		get_color_ui_found = git_config_colorbool(var, value);
	return 0;
}