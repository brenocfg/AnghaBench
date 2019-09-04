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
struct TYPE_3__ {int checkout_strategy; } ;

/* Variables and functions */
 int GIT_CHECKOUT_RECREATE_MISSING ; 
 int GIT_CHECKOUT_SAFE ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  assert_name_is (char*) ; 
 TYPE_1__ checkout_opts ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_write2file (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_path_isdir (char*) ; 
 int /*<<< orphan*/  obj ; 
 int /*<<< orphan*/  repo ; 

void test_checkout_icase__refuses_to_overwrite_files_for_folders(void)
{
	checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE|GIT_CHECKOUT_RECREATE_MISSING;

	cl_git_write2file("testrepo/A", "neue file\n", 10, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);

	cl_git_fail(git_checkout_tree(repo, obj, &checkout_opts));
	assert_name_is("testrepo/A");
	cl_assert(!git_path_isdir("testrepo/A"));
}