#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_checkout_options ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  add_conflict (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void test_checkout_index__writes_conflict_file(void)
{
	git_index *index;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_buf conflicting_buf = GIT_BUF_INIT;

	cl_git_pass(git_repository_index(&index, g_repo));

	add_conflict(index, "conflicting.txt");
	cl_git_pass(git_index_write(index));

	cl_git_pass(git_checkout_index(g_repo, NULL, &opts));

	cl_git_pass(git_futils_readbuffer(&conflicting_buf, "testrepo/conflicting.txt"));
	cl_assert(strcmp(conflicting_buf.ptr,
		"<<<<<<< ours\n"
		"this file is changed in master and branch\n"
		"=======\n"
		"this file is changed in branch and master\n"
		">>>>>>> theirs\n") == 0);
	git_buf_dispose(&conflicting_buf);

	git_index_free(index);
}