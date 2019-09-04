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
struct TYPE_5__ {int /*<<< orphan*/  iterator_time; int /*<<< orphan*/  commit_pool; int /*<<< orphan*/  commits; int /*<<< orphan*/  odb; } ;
typedef  TYPE_1__ git_revwalk ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oidmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pqueue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_reset (TYPE_1__*) ; 

void git_revwalk_free(git_revwalk *walk)
{
	if (walk == NULL)
		return;

	git_revwalk_reset(walk);
	git_odb_free(walk->odb);

	git_oidmap_free(walk->commits);
	git_pool_clear(&walk->commit_pool);
	git_pqueue_free(&walk->iterator_time);
	git__free(walk);
}