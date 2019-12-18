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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  assert_condition_includes (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sandbox_path (int /*<<< orphan*/ *,char*) ; 

void test_config_conditionals__gitdir_i(void)
{
	git_buf path = GIT_BUF_INIT;

	assert_condition_includes("gitdir/i", sandbox_path(&path, "empty_standard_repo/"), true);
	assert_condition_includes("gitdir/i", sandbox_path(&path, "EMPTY_STANDARD_REPO/"), true);

	git_buf_dispose(&path);
}