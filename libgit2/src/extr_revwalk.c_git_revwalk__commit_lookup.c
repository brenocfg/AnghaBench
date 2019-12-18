#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  commits; } ;
typedef  TYPE_1__ git_revwalk ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_10__ {int /*<<< orphan*/  oid; } ;
typedef  TYPE_2__ git_commit_list_node ;

/* Variables and functions */
 TYPE_2__* git_commit_list_alloc_node (TYPE_1__*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 TYPE_2__* git_oidmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ git_oidmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 

git_commit_list_node *git_revwalk__commit_lookup(
	git_revwalk *walk, const git_oid *oid)
{
	git_commit_list_node *commit;

	/* lookup and reserve space if not already present */
	if ((commit = git_oidmap_get(walk->commits, oid)) != NULL)
		return commit;

	commit = git_commit_list_alloc_node(walk);
	if (commit == NULL)
		return NULL;

	git_oid_cpy(&commit->oid, oid);

	if ((git_oidmap_set(walk->commits, &commit->oid, commit)) < 0)
		return NULL;

	return commit;
}