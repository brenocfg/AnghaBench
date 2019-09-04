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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_id ; 
 int /*<<< orphan*/  commit_obj ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_object_pass (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_object_raw_hash__hash_commit_object(void)
{
	git_oid id1, id2;

	cl_git_pass(git_oid_fromstr(&id1, commit_id));
	hash_object_pass(&id2, &commit_obj);
	cl_assert(git_oid_cmp(&id1, &id2) == 0);
}