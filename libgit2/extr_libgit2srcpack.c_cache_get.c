#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ last_usage; int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ git_pack_cache_entry ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  use_ctr; int /*<<< orphan*/  entries; } ;
typedef  TYPE_2__ git_pack_cache ;
typedef  int /*<<< orphan*/  git_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  git_atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ git_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_offmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static git_pack_cache_entry *cache_get(git_pack_cache *cache, git_off_t offset)
{
	git_pack_cache_entry *entry;

	if (git_mutex_lock(&cache->lock) < 0)
		return NULL;

	if ((entry = git_offmap_get(cache->entries, offset)) != NULL) {
		git_atomic_inc(&entry->refcount);
		entry->last_usage = cache->use_ctr++;
	}
	git_mutex_unlock(&cache->lock);

	return entry;
}