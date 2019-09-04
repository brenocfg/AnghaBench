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
struct option {scalar_t__ value; int /*<<< orphan*/  long_name; scalar_t__ defval; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_config_colorbool (int /*<<< orphan*/ *,char const*) ; 

int parse_opt_color_flag_cb(const struct option *opt, const char *arg,
			    int unset)
{
	int value;

	if (!arg)
		arg = unset ? "never" : (const char *)opt->defval;
	value = git_config_colorbool(NULL, arg);
	if (value < 0)
		return error(_("option `%s' expects \"always\", \"auto\", or \"never\""),
			     opt->long_name);
	*(int *)opt->value = value;
	return 0;
}