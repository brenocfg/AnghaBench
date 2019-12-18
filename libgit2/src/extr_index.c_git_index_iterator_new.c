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
struct TYPE_6__ {int /*<<< orphan*/ * index; int /*<<< orphan*/  snap; } ;
typedef  TYPE_1__ git_index_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int git_index_snapshot_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_index_iterator_new(
	git_index_iterator **iterator_out,
	git_index *index)
{
	git_index_iterator *it;
	int error;

	assert(iterator_out && index);

	it = git__calloc(1, sizeof(git_index_iterator));
	GIT_ERROR_CHECK_ALLOC(it);

	if ((error = git_index_snapshot_new(&it->snap, index)) < 0) {
		git__free(it);
		return error;
	}

	it->index = index;

	*iterator_out = it;
	return 0;
}