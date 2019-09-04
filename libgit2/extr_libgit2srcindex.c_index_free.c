#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* index_file_path; int /*<<< orphan*/  deleted; int /*<<< orphan*/  reuc; int /*<<< orphan*/  names; int /*<<< orphan*/  entries; int /*<<< orphan*/  entries_map; int /*<<< orphan*/  readers; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git__memzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_atomic_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_idxmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_vector_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void index_free(git_index *index)
{
	/* index iterators increment the refcount of the index, so if we
	 * get here then there should be no outstanding iterators.
	 */
	assert(!git_atomic_get(&index->readers));

	git_index_clear(index);
	git_idxmap_free(index->entries_map);
	git_vector_free(&index->entries);
	git_vector_free(&index->names);
	git_vector_free(&index->reuc);
	git_vector_free(&index->deleted);

	git__free(index->index_file_path);

	git__memzero(index, sizeof(*index));
	git__free(index);
}