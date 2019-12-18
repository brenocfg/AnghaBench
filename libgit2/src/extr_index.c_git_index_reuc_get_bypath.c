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
typedef  int /*<<< orphan*/  git_index_reuc_entry ;
struct TYPE_7__ {int /*<<< orphan*/  length; } ;
struct TYPE_6__ {TYPE_2__ reuc; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git_index_reuc_find (size_t*,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  const* git_vector_get (TYPE_2__*,size_t) ; 
 int git_vector_is_sorted (TYPE_2__*) ; 

const git_index_reuc_entry *git_index_reuc_get_bypath(
	git_index *index, const char *path)
{
	size_t pos;
	assert(index && path);

	if (!index->reuc.length)
		return NULL;

	assert(git_vector_is_sorted(&index->reuc));

	if (git_index_reuc_find(&pos, index, path) < 0)
		return NULL;

	return git_vector_get(&index->reuc, pos);
}