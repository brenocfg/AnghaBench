#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t length; int /*<<< orphan*/ * contents; } ;
struct TYPE_5__ {int dirty; TYPE_2__ reuc; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git__swap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  index_entry_reuc_free (int /*<<< orphan*/ ) ; 

void git_index_reuc_clear(git_index *index)
{
	size_t i;

	assert(index);

	for (i = 0; i < index->reuc.length; ++i)
		index_entry_reuc_free(git__swap(index->reuc.contents[i], NULL));

	git_vector_clear(&index->reuc);

	index->dirty = 1;
}