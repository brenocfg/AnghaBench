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
 int /*<<< orphan*/  cl_setenv (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_git_env(void)
{
	cl_setenv("GIT_DIR", NULL);
	cl_setenv("GIT_CEILING_DIRECTORIES", NULL);
	cl_setenv("GIT_INDEX_FILE", NULL);
	cl_setenv("GIT_NAMESPACE", NULL);
	cl_setenv("GIT_OBJECT_DIRECTORY", NULL);
	cl_setenv("GIT_ALTERNATE_OBJECT_DIRECTORIES", NULL);
	cl_setenv("GIT_WORK_TREE", NULL);
	cl_setenv("GIT_COMMON_DIR", NULL);
}