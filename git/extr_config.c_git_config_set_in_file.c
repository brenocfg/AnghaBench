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
 int /*<<< orphan*/  git_config_set_multivar_in_file (char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void git_config_set_in_file(const char *config_filename,
			    const char *key, const char *value)
{
	git_config_set_multivar_in_file(config_filename, key, value, NULL, 0);
}