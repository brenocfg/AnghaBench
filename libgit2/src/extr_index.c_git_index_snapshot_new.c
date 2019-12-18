#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_vector ;
struct TYPE_8__ {int /*<<< orphan*/  _cmp; } ;
struct TYPE_7__ {TYPE_2__ entries; int /*<<< orphan*/  readers; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_1__*) ; 
 int /*<<< orphan*/  git_atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_snapshot_release (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int git_vector_dup (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_sort (TYPE_2__*) ; 

int git_index_snapshot_new(git_vector *snap, git_index *index)
{
	int error;

	GIT_REFCOUNT_INC(index);

	git_atomic_inc(&index->readers);
	git_vector_sort(&index->entries);

	error = git_vector_dup(snap, &index->entries, index->entries._cmp);

	if (error < 0)
		git_index_snapshot_release(snap, index);

	return error;
}