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
 int /*<<< orphan*/  git_config_set_multivar (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace2_cmd_set_config (char const*,char const*) ; 

void git_config_set(const char *key, const char *value)
{
	git_config_set_multivar(key, value, NULL, 0);

	trace2_cmd_set_config(key, value);
}