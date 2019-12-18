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
struct TYPE_3__ {char** oids; int /*<<< orphan*/  invokes; } ;

/* Variables and functions */
 int /*<<< orphan*/  REPO_NAME ; 
 int /*<<< orphan*/  callback_cb ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__ data ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  repo ; 

void test_stash_foreach__enumerating_a_empty_repository_doesnt_fail(void)
{
	char *oids[] = { NULL };

	data.oids = oids;

	cl_git_pass(git_repository_init(&repo, REPO_NAME, 0));

	cl_git_pass(git_stash_foreach(repo, callback_cb, &data));

	cl_assert_equal_i(0, data.invokes);
}