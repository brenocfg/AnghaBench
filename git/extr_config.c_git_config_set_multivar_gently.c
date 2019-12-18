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
 int git_config_set_multivar_in_file_gently (int /*<<< orphan*/ *,char const*,char const*,char const*,int) ; 

int git_config_set_multivar_gently(const char *key, const char *value,
				   const char *value_regex, int multi_replace)
{
	return git_config_set_multivar_in_file_gently(NULL, key, value, value_regex,
						      multi_replace);
}