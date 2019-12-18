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
typedef  int /*<<< orphan*/  git_strarray ;
struct TYPE_5__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  pathspec; int /*<<< orphan*/  prefix; } ;
typedef  TYPE_1__ git_pathspec ;

/* Variables and functions */
 int /*<<< orphan*/  git_pathspec__clear (TYPE_1__*) ; 
 int git_pathspec__vinit (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_prefix (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int git_pathspec__init(git_pathspec *ps, const git_strarray *paths)
{
	int error = 0;

	memset(ps, 0, sizeof(*ps));

	ps->prefix = git_pathspec_prefix(paths);
	git_pool_init(&ps->pool, 1);

	if ((error = git_pathspec__vinit(&ps->pathspec, paths, &ps->pool)) < 0)
		git_pathspec__clear(ps);

	return error;
}