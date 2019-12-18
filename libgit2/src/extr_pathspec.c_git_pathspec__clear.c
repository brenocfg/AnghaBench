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
struct TYPE_4__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  pathspec; int /*<<< orphan*/  prefix; } ;
typedef  TYPE_1__ git_pathspec ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pathspec__vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void git_pathspec__clear(git_pathspec *ps)
{
	git__free(ps->prefix);
	git_pathspec__vfree(&ps->pathspec);
	git_pool_clear(&ps->pool);
	memset(ps, 0, sizeof(*ps));
}