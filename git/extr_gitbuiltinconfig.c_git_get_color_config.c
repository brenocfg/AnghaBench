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
 scalar_t__ color_parse (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_error_nonbool (char const*) ; 
 int get_color_found ; 
 int /*<<< orphan*/  get_color_slot ; 
 int /*<<< orphan*/  parsed_color ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int git_get_color_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, get_color_slot)) {
		if (!value)
			config_error_nonbool(var);
		if (color_parse(value, parsed_color) < 0)
			return -1;
		get_color_found = 1;
	}
	return 0;
}