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
 int /*<<< orphan*/  EXEC_PATH_ENVIRONMENT ; 
 char const* exec_path_value ; 
 int /*<<< orphan*/  setenv (int /*<<< orphan*/ ,char const*,int) ; 

void git_set_exec_path(const char *exec_path)
{
	exec_path_value = exec_path;
	/*
	 * Propagate this setting to external programs.
	 */
	setenv(EXEC_PATH_ENVIRONMENT, exec_path, 1);
}