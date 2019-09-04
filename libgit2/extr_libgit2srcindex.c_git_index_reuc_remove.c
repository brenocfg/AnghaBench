#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_index_reuc_entry ;
struct TYPE_3__ {int dirty; int /*<<< orphan*/  reuc; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_vector_get (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_vector_is_sorted (int /*<<< orphan*/ *) ; 
 int git_vector_remove (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  index_entry_reuc_free (int /*<<< orphan*/ *) ; 

int git_index_reuc_remove(git_index *index, size_t position)
{
	int error;
	git_index_reuc_entry *reuc;

	assert(git_vector_is_sorted(&index->reuc));

	reuc = git_vector_get(&index->reuc, position);
	error = git_vector_remove(&index->reuc, position);

	if (!error)
		index_entry_reuc_free(reuc);

	index->dirty = 1;
	return error;
}