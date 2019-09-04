#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_path_diriter ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_8__ {TYPE_1__ path; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  GIT_PATH_DIRITER_INIT ; 
 int /*<<< orphan*/  check_counts (TYPE_2__*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dirent_cleanup__cb ; 
 int /*<<< orphan*/  git_path_diriter_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_diriter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_path_diriter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_next (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  setup (TYPE_2__*) ; 
 TYPE_2__ sub ; 

void test_core_dirent__diriter_with_fullname(void)
{
	git_path_diriter diriter = GIT_PATH_DIRITER_INIT;
	int error;

	cl_set_cleanup(&dirent_cleanup__cb, &sub);
	setup(&sub);

	cl_git_pass(git_path_diriter_init(&diriter, sub.path.ptr, 0));

	while ((error = git_path_diriter_next(&diriter)) == 0)
		handle_next(&diriter, &sub);

	cl_assert_equal_i(error, GIT_ITEROVER);

	git_path_diriter_free(&diriter);

	check_counts(&sub);
}