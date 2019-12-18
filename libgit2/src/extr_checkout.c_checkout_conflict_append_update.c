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
typedef  int /*<<< orphan*/  git_index_entry ;
struct TYPE_9__ {int /*<<< orphan*/  update_conflicts; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ checkout_data ;
struct TYPE_10__ {int /*<<< orphan*/  const* theirs; int /*<<< orphan*/  const* ours; int /*<<< orphan*/  const* ancestor; } ;
typedef  TYPE_2__ checkout_conflictdata ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int checkout_conflict_detect_binary (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int checkout_conflict_detect_submodule (TYPE_2__*) ; 
 TYPE_2__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int checkout_conflict_append_update(
	const git_index_entry *ancestor,
	const git_index_entry *ours,
	const git_index_entry *theirs,
	void *payload)
{
	checkout_data *data = payload;
	checkout_conflictdata *conflict;
	int error;

	conflict = git__calloc(1, sizeof(checkout_conflictdata));
	GIT_ERROR_CHECK_ALLOC(conflict);

	conflict->ancestor = ancestor;
	conflict->ours = ours;
	conflict->theirs = theirs;

	if ((error = checkout_conflict_detect_submodule(conflict)) < 0 ||
		(error = checkout_conflict_detect_binary(data->repo, conflict)) < 0)
	{
		git__free(conflict);
		return error;
	}

	if (git_vector_insert(&data->update_conflicts, conflict))
		return -1;

	return 0;
}