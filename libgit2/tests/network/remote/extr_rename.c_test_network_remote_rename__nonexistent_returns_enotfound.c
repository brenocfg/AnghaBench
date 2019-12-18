#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_strarray ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int git_remote_rename (TYPE_1__*,int /*<<< orphan*/ ,char*,char*) ; 

void test_network_remote_rename__nonexistent_returns_enotfound(void)
{
	git_strarray problems = {0};

	int err = git_remote_rename(&problems, _repo, "nonexistent", "renamed");

	cl_assert_equal_i(GIT_ENOTFOUND, err);
}