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
 int config_error_nonbool (char const*) ; 
 char* xstrdup (char const*) ; 

int git_config_string(const char **dest, const char *var, const char *value)
{
	if (!value)
		return config_error_nonbool(var);
	*dest = xstrdup(value);
	return 0;
}