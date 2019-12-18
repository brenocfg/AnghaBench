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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  git_blame_hunk ;
struct TYPE_5__ {int /*<<< orphan*/  hunks; } ;
typedef  TYPE_1__ git_blame ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  const* git_blame_get_hunk_byindex (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_bsearch2 (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  hunk_byfinalline_search_cmp ; 

const git_blame_hunk *git_blame_get_hunk_byline(git_blame *blame, size_t lineno)
{
	size_t i, new_lineno = lineno;
	assert(blame);

	if (!git_vector_bsearch2(&i, &blame->hunks, hunk_byfinalline_search_cmp, &new_lineno)) {
		return git_blame_get_hunk_byindex(blame, (uint32_t)i);
	}

	return NULL;
}