#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  push; } ;

/* Variables and functions */
 TYPE_1__* _refspec ; 
 int /*<<< orphan*/  _remote ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_b (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_refspec_dst (TYPE_1__*) ; 
 int /*<<< orphan*/  git_refspec_src (TYPE_1__*) ; 
 int /*<<< orphan*/  git_refspec_string (TYPE_1__*) ; 
 int /*<<< orphan*/  git_remote_add_push (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* git_remote_get_refspec (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 size_t git_remote_refspec_count (int /*<<< orphan*/ ) ; 

void test_network_remote_remotes__add_pushspec(void)
{
	size_t size;

	size = git_remote_refspec_count(_remote);

	cl_git_pass(git_remote_add_push(_repo, "test", "refs/*:refs/*"));
	size++;

	git_remote_free(_remote);
	cl_git_pass(git_remote_lookup(&_remote, _repo, "test"));

	cl_assert_equal_i((int)size, (int)git_remote_refspec_count(_remote));

	_refspec = git_remote_get_refspec(_remote, size - 1);
	cl_assert_equal_s(git_refspec_src(_refspec), "refs/*");
	cl_assert_equal_s(git_refspec_dst(_refspec), "refs/*");
	cl_assert_equal_s(git_refspec_string(_refspec), "refs/*:refs/*");

	cl_assert_equal_b(_refspec->push, true);
}