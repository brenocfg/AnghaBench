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
struct TYPE_8__ {int /*<<< orphan*/  attr; } ;
typedef  TYPE_1__ git_tree_entry ;
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  path; int /*<<< orphan*/  repo; } ;
typedef  TYPE_2__ git_submodule ;

/* Variables and functions */
 int GIT_SUBMODULE_STATUS_IN_HEAD ; 
 int GIT_SUBMODULE_STATUS__HEAD_OID_VALID ; 
 int /*<<< orphan*/  git_error_clear () ; 
 scalar_t__ git_repository_head_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ git_tree_entry_bypath (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_entry_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_tree_entry_id (TYPE_1__*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submodule_update_from_head_data (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int submodule_update_head(git_submodule *submodule)
{
	git_tree *head = NULL;
	git_tree_entry *te = NULL;

	submodule->flags = submodule->flags &
		~(GIT_SUBMODULE_STATUS_IN_HEAD |
		  GIT_SUBMODULE_STATUS__HEAD_OID_VALID);

	/* if we can't look up file in current head, then done */
	if (git_repository_head_tree(&head, submodule->repo) < 0 ||
		git_tree_entry_bypath(&te, head, submodule->path) < 0)
		git_error_clear();
	else
		submodule_update_from_head_data(submodule, te->attr, git_tree_entry_id(te));

	git_tree_entry_free(te);
	git_tree_free(head);
	return 0;
}