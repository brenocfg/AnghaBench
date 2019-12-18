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
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  assert_condition_includes (char*,char*,int) ; 
 int /*<<< orphan*/  set_head (int /*<<< orphan*/ ,char*) ; 

void test_config_conditionals__onbranch(void)
{
	assert_condition_includes("onbranch", "master", true);
	assert_condition_includes("onbranch", "m*", true);
	assert_condition_includes("onbranch", "*", true);
	assert_condition_includes("onbranch", "master/", false);
	assert_condition_includes("onbranch", "foo", false);

	set_head(_repo, "foo");
	assert_condition_includes("onbranch", "master", false);
	assert_condition_includes("onbranch", "foo", true);
	assert_condition_includes("onbranch", "f*o", true);

	set_head(_repo, "dir/ref");
	assert_condition_includes("onbranch", "dir/ref", true);
	assert_condition_includes("onbranch", "dir/", true);
	assert_condition_includes("onbranch", "dir/*", true);
	assert_condition_includes("onbranch", "dir/**", true);
	assert_condition_includes("onbranch", "**", true);
	assert_condition_includes("onbranch", "dir", false);
	assert_condition_includes("onbranch", "dir*", false);

	set_head(_repo, "dir/subdir/ref");
	assert_condition_includes("onbranch", "dir/subdir/", true);
	assert_condition_includes("onbranch", "dir/subdir/*", true);
	assert_condition_includes("onbranch", "dir/subdir/ref", true);
	assert_condition_includes("onbranch", "dir/", true);
	assert_condition_includes("onbranch", "dir/**", true);
	assert_condition_includes("onbranch", "**", true);
	assert_condition_includes("onbranch", "dir", false);
	assert_condition_includes("onbranch", "dir*", false);
	assert_condition_includes("onbranch", "dir/*", false);
}