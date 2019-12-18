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
 int git_config_pathname (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  init_db_template_dir ; 
 int platform_core_config (char const*,char const*,void*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int git_init_db_config(const char *k, const char *v, void *cb)
{
	if (!strcmp(k, "init.templatedir"))
		return git_config_pathname(&init_db_template_dir, k, v);

	if (starts_with(k, "core."))
		return platform_core_config(k, v, cb);

	return 0;
}