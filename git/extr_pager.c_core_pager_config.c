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
 int git_config_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  pager_program ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int core_pager_config(const char *var, const char *value, void *data)
{
	if (!strcmp(var, "core.pager"))
		return git_config_string(&pager_program, var, value);
	return 0;
}