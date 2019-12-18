#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct repository {TYPE_1__* index; } ;
struct lock_file {int dummy; } ;
struct TYPE_3__ {scalar_t__ cache_changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_LOCK ; 
 scalar_t__ has_racy_timestamp (TYPE_1__*) ; 
 scalar_t__ repo_verify_index (struct repository*) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  write_locked_index (TYPE_1__*,struct lock_file*,int /*<<< orphan*/ ) ; 

void repo_update_index_if_able(struct repository *repo,
			       struct lock_file *lockfile)
{
	if ((repo->index->cache_changed ||
	     has_racy_timestamp(repo->index)) &&
	    repo_verify_index(repo))
		write_locked_index(repo->index, lockfile, COMMIT_LOCK);
	else
		rollback_lock_file(lockfile);
}