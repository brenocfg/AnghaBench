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
 int RECURSE_SUBMODULES_ERROR ; 
 int RECURSE_SUBMODULES_OFF ; 
 int RECURSE_SUBMODULES_ON ; 
 int /*<<< orphan*/  die (char*,char const*,char const*) ; 
 int git_parse_maybe_bool (char const*) ; 

__attribute__((used)) static int parse_update_recurse(const char *opt, const char *arg,
				int die_on_error)
{
	switch (git_parse_maybe_bool(arg)) {
	case 1:
		return RECURSE_SUBMODULES_ON;
	case 0:
		return RECURSE_SUBMODULES_OFF;
	default:
		if (die_on_error)
			die("bad %s argument: %s", opt, arg);
		return RECURSE_SUBMODULES_ERROR;
	}
}