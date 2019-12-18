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
 int execv_git_cmd (char const**) ; 

__attribute__((used)) static int ut_005exec(int argc, const char **argv)
{
	int result;

	if (!argc)
		return 0;

	result = execv_git_cmd(argv);
	return result;
}