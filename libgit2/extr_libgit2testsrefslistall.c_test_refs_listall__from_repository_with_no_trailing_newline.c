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

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_list (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 
 TYPE_1__ ref_list ; 
 int /*<<< orphan*/  repo ; 

void test_refs_listall__from_repository_with_no_trailing_newline(void)
{
	cl_git_pass(git_repository_open(&repo, cl_fixture("bad_tag.git")));
	cl_git_pass(git_reference_list(&ref_list, repo));

	cl_assert(ref_list.count > 0);

	git_strarray_free(&ref_list);
	git_repository_free(repo);
}