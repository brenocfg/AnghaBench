#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  map; int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ git_sortedcache ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_rwlock_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_sortedcache_wlock (TYPE_1__*) ; 
 int /*<<< orphan*/  git_sortedcache_wunlock (TYPE_1__*) ; 
 int /*<<< orphan*/  git_strmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sortedcache_clear (TYPE_1__*) ; 

__attribute__((used)) static void sortedcache_free(git_sortedcache *sc)
{
	/* acquire write lock to make sure everyone else is done */
	if (git_sortedcache_wlock(sc) < 0)
		return;

	sortedcache_clear(sc);
	git_vector_free(&sc->items);
	git_strmap_free(sc->map);

	git_sortedcache_wunlock(sc);

	git_rwlock_free(&sc->lock);
	git__free(sc);
}