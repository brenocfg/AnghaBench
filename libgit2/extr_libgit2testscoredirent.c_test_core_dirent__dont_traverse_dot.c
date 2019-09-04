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
struct TYPE_6__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_counts (TYPE_1__*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dirent_cleanup__cb ; 
 TYPE_1__ dot ; 
 int /*<<< orphan*/  git_path_direach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  one_entry ; 
 int /*<<< orphan*/  setup (TYPE_1__*) ; 

void test_core_dirent__dont_traverse_dot(void)
{
	cl_set_cleanup(&dirent_cleanup__cb, &dot);
	setup(&dot);

	cl_git_pass(git_path_direach(&dot.path, 0, one_entry, &dot));

	check_counts(&dot);
}