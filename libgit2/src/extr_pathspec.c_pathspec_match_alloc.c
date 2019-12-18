#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int datatype; int /*<<< orphan*/ * pathspec; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ git_pathspec_match_list ;
typedef  int /*<<< orphan*/  git_pathspec ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_INC (int /*<<< orphan*/ *) ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static git_pathspec_match_list *pathspec_match_alloc(
	git_pathspec *ps, int datatype)
{
	git_pathspec_match_list *m = git__calloc(1, sizeof(git_pathspec_match_list));
	if (!m)
		return NULL;

	git_pool_init(&m->pool, 1);

	/* need to keep reference to pathspec and increment refcount because
	 * failures array stores pointers to the pattern strings of the
	 * pathspec that had no matches
	 */
	GIT_REFCOUNT_INC(ps);
	m->pathspec = ps;
	m->datatype = datatype;

	return m;
}