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
typedef  TYPE_1__ git_cache ;

/* Variables and functions */
 int /*<<< orphan*/  clear_cache (TYPE_1__*) ; 
 scalar_t__ git_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rwlock_wrunlock (int /*<<< orphan*/ *) ; 

void git_cache_clear(git_cache *cache)
{
	if (git_rwlock_wrlock(&cache->lock) < 0)
		return;

	clear_cache(cache);

	git_rwlock_wrunlock(&cache->lock);
}