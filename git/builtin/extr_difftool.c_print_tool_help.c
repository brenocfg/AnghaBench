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
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 int run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int print_tool_help(void)
{
	const char *argv[] = { "mergetool", "--tool-help=diff", NULL };
	return run_command_v_opt(argv, RUN_GIT_CMD);
}