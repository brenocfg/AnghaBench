#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_packbuilder ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_commit_tree_id (int /*<<< orphan*/ *) ; 
 scalar_t__ git_packbuilder_insert (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ git_packbuilder_insert_tree (TYPE_1__*,int /*<<< orphan*/ ) ; 

int git_packbuilder_insert_commit(git_packbuilder *pb, const git_oid *oid)
{
	git_commit *commit;

	if (git_commit_lookup(&commit, pb->repo, oid) < 0 ||
		git_packbuilder_insert(pb, oid, NULL) < 0)
		return -1;

	if (git_packbuilder_insert_tree(pb, git_commit_tree_id(commit)) < 0)
		return -1;

	git_commit_free(commit);
	return 0;
}