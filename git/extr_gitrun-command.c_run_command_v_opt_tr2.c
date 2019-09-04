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
 int run_command_v_opt_cd_env_tr2 (char const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

int run_command_v_opt_tr2(const char **argv, int opt, const char *tr2_class)
{
	return run_command_v_opt_cd_env_tr2(argv, opt, NULL, NULL, tr2_class);
}