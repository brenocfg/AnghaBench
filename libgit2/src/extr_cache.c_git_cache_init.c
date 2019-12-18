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
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ git_cache ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_oidmap_new (int /*<<< orphan*/ *) ; 
 scalar_t__ git_rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int git_cache_init(git_cache *cache)
{
	memset(cache, 0, sizeof(*cache));

	if ((git_oidmap_new(&cache->map)) < 0)
		return -1;

	if (git_rwlock_init(&cache->lock)) {
		git_error_set(GIT_ERROR_OS, "failed to initialize cache rwlock");
		return -1;
	}

	return 0;
}