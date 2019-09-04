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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ git_sortedcache ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  GIT_UNUSED (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_rwlock_wrlock (int /*<<< orphan*/ *) ; 

int git_sortedcache_wlock(git_sortedcache *sc)
{
	GIT_UNUSED(sc); /* prevent warning when compiled w/o threads */

	if (git_rwlock_wrlock(&sc->lock) < 0) {
		git_error_set(GIT_ERROR_OS, "unable to acquire write lock on cache");
		return -1;
	}
	return 0;
}