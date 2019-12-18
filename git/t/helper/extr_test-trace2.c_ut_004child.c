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
 int /*<<< orphan*/  exit (int) ; 
 int run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ut_004child(int argc, const char **argv)
{
	int result;

	/*
	 * Allow empty <child_command_line> so we can do arbitrarily deep
	 * command nesting and let the last one be null.
	 */
	if (!argc)
		return 0;

	result = run_command_v_opt(argv, 0);
	exit(result);
}