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
 int /*<<< orphan*/  git_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  ident_use_config_only ; 
 int set_ident (char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int git_ident_config(const char *var, const char *value, void *data)
{
	if (!strcmp(var, "user.useconfigonly")) {
		ident_use_config_only = git_config_bool(var, value);
		return 0;
	}

	return set_ident(var, value);
}