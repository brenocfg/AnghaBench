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
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_7__ {TYPE_2__ path; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_counts (TYPE_1__*) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dirent_cleanup__cb ; 
 TYPE_1__ empty ; 
 int /*<<< orphan*/  git_path_direach (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_path_is_empty_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  one_entry ; 
 int /*<<< orphan*/  setup (TYPE_1__*) ; 

void test_core_dirent__dont_traverse_empty_folders(void)
{
	cl_set_cleanup(&dirent_cleanup__cb, &empty);
	setup(&empty);

	cl_git_pass(git_path_direach(&empty.path, 0, one_entry, &empty));

	check_counts(&empty);

	/* make sure callback not called */
	cl_assert(git_path_is_empty_dir(empty.path.ptr));
}