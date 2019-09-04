#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ count; } ;
typedef  TYPE_1__ git_strarray ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_tag_list (TYPE_1__*,int /*<<< orphan*/ ) ; 

void test_object_tag_list__list_all(void)
{
	/* list all tag names from the repository */
	git_strarray tag_list;

	cl_git_pass(git_tag_list(&tag_list, g_repo));

	cl_assert_equal_i((int)tag_list.count, 6);

	git_strarray_free(&tag_list);
}