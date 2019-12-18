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
struct TYPE_5__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  deltas; int /*<<< orphan*/  attrsession; } ;
struct TYPE_6__ {TYPE_1__ base; int /*<<< orphan*/  pathspec; } ;
typedef  TYPE_2__ git_diff_generated ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 int /*<<< orphan*/  git__memzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  git_attr_session__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec__vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free_deep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void diff_generated_free(git_diff *d)
{
	git_diff_generated *diff = (git_diff_generated *)d;

	git_attr_session__free(&diff->base.attrsession);
	git_vector_free_deep(&diff->base.deltas);

	git_pathspec__vfree(&diff->pathspec);
	git_pool_clear(&diff->base.pool);

	git__memzero(diff, sizeof(*diff));
	git__free(diff);
}