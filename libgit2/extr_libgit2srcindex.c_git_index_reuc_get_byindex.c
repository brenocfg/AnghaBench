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
typedef  int /*<<< orphan*/  git_index_reuc_entry ;
struct TYPE_5__ {int /*<<< orphan*/  reuc; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  const* git_vector_get (int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__* git_vector_is_sorted (int /*<<< orphan*/ *) ; 

const git_index_reuc_entry *git_index_reuc_get_byindex(
	git_index *index, size_t n)
{
	assert(index);
	assert(git_vector_is_sorted(&index->reuc));

	return git_vector_get(&index->reuc, n);
}