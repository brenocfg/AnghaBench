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
 int repo_config_get_value (int /*<<< orphan*/ ,char const*,char const**) ; 
 int /*<<< orphan*/  the_repository ; 

int git_config_get_value(const char *key, const char **value)
{
	return repo_config_get_value(the_repository, key, value);
}