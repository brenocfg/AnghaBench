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
 int git_config_set_multivar_gently (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int git_config_set_gently(const char *key, const char *value)
{
	return git_config_set_multivar_gently(key, value, NULL, 0);
}