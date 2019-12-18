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
 int /*<<< orphan*/  CONFIG_REGEX_NONE ; 
 int git_config_set_multivar_gently (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_one_config(const char *key, const char *value, void *data)
{
	return git_config_set_multivar_gently(key,
					      value ? value : "true",
					      CONFIG_REGEX_NONE, 0);
}