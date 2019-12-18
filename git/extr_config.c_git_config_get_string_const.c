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
 int repo_config_get_string_const (int /*<<< orphan*/ ,char const*,char const**) ; 
 int /*<<< orphan*/  the_repository ; 

int git_config_get_string_const(const char *key, const char **dest)
{
	return repo_config_get_string_const(the_repository, key, dest);
}