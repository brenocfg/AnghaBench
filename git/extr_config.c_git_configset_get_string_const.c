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
 int git_config_string (char const**,char const*,char const*) ; 
 int /*<<< orphan*/  git_configset_get_value (struct config_set*,char const*,char const**) ; 

int git_configset_get_string_const(struct config_set *cs, const char *key, const char **dest)
{
	const char *value;
	if (!git_configset_get_value(cs, key, &value))
		return git_config_string(dest, key, value);
	else
		return 1;
}