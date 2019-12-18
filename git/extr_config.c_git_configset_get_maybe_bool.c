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
struct config_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_configset_get_value (struct config_set*,char const*,char const**) ; 
 int git_parse_maybe_bool (char const*) ; 

int git_configset_get_maybe_bool(struct config_set *cs, const char *key, int *dest)
{
	const char *value;
	if (!git_configset_get_value(cs, key, &value)) {
		*dest = git_parse_maybe_bool(value);
		if (*dest == -1)
			return -1;
		return 0;
	} else
		return 1;
}