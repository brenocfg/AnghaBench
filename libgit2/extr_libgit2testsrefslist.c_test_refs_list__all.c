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
 int /*<<< orphan*/  git_reference_list (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 

void test_refs_list__all(void)
{
	/* try to list all the references in our test repo */
	git_strarray ref_list;

	cl_git_pass(git_reference_list(&ref_list, g_repo));

	/*{
		unsigned short i;
		for (i = 0; i < ref_list.count; ++i)
			printf("# %s\n", ref_list.strings[i]);
	}*/

	/* We have exactly 12 refs in total if we include the packed ones:
	 * there is a reference that exists both in the packfile and as
	 * loose, but we only list it once */
	cl_assert_equal_i((int)ref_list.count, 18);

	git_strarray_free(&ref_list);
}