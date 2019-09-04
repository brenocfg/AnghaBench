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
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_core_stat__cleanup(void)
{
	git_futils_rmdir_r("root", NULL, GIT_RMDIR_REMOVE_FILES);
}