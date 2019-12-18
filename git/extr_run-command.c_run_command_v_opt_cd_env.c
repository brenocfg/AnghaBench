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
 int run_command_v_opt_cd_env_tr2 (char const**,int,char const*,char const* const*,int /*<<< orphan*/ *) ; 

int run_command_v_opt_cd_env(const char **argv, int opt, const char *dir, const char *const *env)
{
	return run_command_v_opt_cd_env_tr2(argv, opt, dir, env, NULL);
}