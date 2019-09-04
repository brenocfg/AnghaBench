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
struct TYPE_5__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_6__ {scalar_t__ (* entries_cmp_path ) (int /*<<< orphan*/ ,char const*) ;int /*<<< orphan*/  entries; int /*<<< orphan*/  entries_search_path; } ;
typedef  TYPE_2__ git_index ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ git_vector_bsearch2 (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* git_vector_get (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,char const*) ; 

int git_index_find(size_t *at_pos, git_index *index, const char *path)
{
	size_t pos;

	assert(index && path);

	if (git_vector_bsearch2(
			&pos, &index->entries, index->entries_search_path, path) < 0) {
		git_error_set(GIT_ERROR_INDEX, "index does not contain %s", path);
		return GIT_ENOTFOUND;
	}

	/* Since our binary search only looked at path, we may be in the
	 * middle of a list of stages.
	 */
	for (; pos > 0; --pos) {
		const git_index_entry *prev = git_vector_get(&index->entries, pos - 1);

		if (index->entries_cmp_path(prev->path, path) != 0)
			break;
	}

	if (at_pos)
		*at_pos = pos;

	return 0;
}