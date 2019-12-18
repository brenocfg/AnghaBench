#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_8__ {int /*<<< orphan*/  repo; } ;
struct TYPE_9__ {TYPE_1__ object; } ;
typedef  TYPE_2__ git_commit ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_2__ const*) ; 
 int git_commit_lookup (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * git_commit_parent_id (TYPE_2__ const*,unsigned int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,unsigned int) ; 

int git_commit_parent(
	git_commit **parent, const git_commit *commit, unsigned int n)
{
	const git_oid *parent_id;
	assert(commit);

	parent_id = git_commit_parent_id(commit, n);
	if (parent_id == NULL) {
		git_error_set(GIT_ERROR_INVALID, "parent %u does not exist", n);
		return GIT_ENOTFOUND;
	}

	return git_commit_lookup(parent, commit->object.repo, parent_id);
}