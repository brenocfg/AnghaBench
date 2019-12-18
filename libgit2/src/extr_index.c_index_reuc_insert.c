#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * path; } ;
typedef  TYPE_1__ git_index_reuc_entry ;
struct TYPE_7__ {int dirty; int /*<<< orphan*/  reuc; } ;
typedef  TYPE_2__ git_index ;

/* Variables and functions */
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int git_vector_insert_sorted (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int git_vector_is_sorted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_reuc_on_dup ; 

__attribute__((used)) static int index_reuc_insert(
	git_index *index,
	git_index_reuc_entry *reuc)
{
	int res;

	assert(index && reuc && reuc->path != NULL);
	assert(git_vector_is_sorted(&index->reuc));

	res = git_vector_insert_sorted(&index->reuc, reuc, &index_reuc_on_dup);
	index->dirty = 1;

	return res == GIT_EEXISTS ? 0 : res;
}