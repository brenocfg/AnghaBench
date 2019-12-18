#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ ) ; 
 scalar_t__ git_object_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_streq (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_tag_peel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  retrieve_tag_from_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tag ; 
 int /*<<< orphan*/  target ; 

void test_object_tag_peel__can_peel_several_nested_tags_to_a_commit(void)
{
	retrieve_tag_from_oid(&tag, repo, "b25fa35b38051e4ae45d4222e795f9df2e43f1d1");

	cl_git_pass(git_tag_peel(&target, tag));
	cl_assert(git_object_type(target) == GIT_OBJECT_COMMIT);
	cl_git_pass(git_oid_streq(git_object_id(target), "e90810b8df3e80c413d903f631643c716887138d"));
}