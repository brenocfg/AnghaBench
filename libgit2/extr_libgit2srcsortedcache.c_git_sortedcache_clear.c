#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_sortedcache ;

/* Variables and functions */
 scalar_t__ git_sortedcache_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_sortedcache_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sortedcache_clear (int /*<<< orphan*/ *) ; 

int git_sortedcache_clear(git_sortedcache *sc, bool wlock)
{
	if (wlock && git_sortedcache_wlock(sc) < 0)
		return -1;

	sortedcache_clear(sc);

	if (wlock)
		git_sortedcache_wunlock(sc);

	return 0;
}