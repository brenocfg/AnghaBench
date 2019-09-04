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
struct option {int* value; int /*<<< orphan*/  long_name; } ;

/* Variables and functions */
 int RECURSE_SUBMODULES_OFF ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int parse_push_recurse_submodules_arg (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int option_parse_recurse_submodules(const struct option *opt,
				   const char *arg, int unset)
{
	int *recurse_submodules = opt->value;

	if (unset)
		*recurse_submodules = RECURSE_SUBMODULES_OFF;
	else if (arg)
		*recurse_submodules = parse_push_recurse_submodules_arg(opt->long_name, arg);
	else
		die("%s missing parameter", opt->long_name);

	return 0;
}