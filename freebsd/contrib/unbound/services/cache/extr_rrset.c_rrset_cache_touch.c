#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ hash; int /*<<< orphan*/  lock; } ;
struct ub_packed_rrset_key {scalar_t__ id; TYPE_1__ entry; } ;
struct rrset_cache {int /*<<< orphan*/  table; } ;
struct lruhash {int /*<<< orphan*/  lock; } ;
typedef  scalar_t__ rrset_id_type ;
typedef  scalar_t__ hashvalue_type ;

/* Variables and functions */
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_touch (struct lruhash*,TYPE_1__*) ; 
 struct lruhash* slabhash_gettable (int /*<<< orphan*/ *,scalar_t__) ; 

void 
rrset_cache_touch(struct rrset_cache* r, struct ub_packed_rrset_key* key,
        hashvalue_type hash, rrset_id_type id)
{
	struct lruhash* table = slabhash_gettable(&r->table, hash);
	/* 
	 * This leads to locking problems, deadlocks, if the caller is 
	 * holding any other rrset lock.
	 * Because a lookup through the hashtable does:
	 *	tablelock -> entrylock  (for that entry caller holds)
	 * And this would do
	 *	entrylock(already held) -> tablelock
	 * And if two threads do this, it results in deadlock.
	 * So, the caller must not hold entrylock.
	 */
	lock_quick_lock(&table->lock);
	/* we have locked the hash table, the item can still be deleted.
	 * because it could already have been reclaimed, but not yet set id=0.
	 * This is because some lruhash routines have lazy deletion.
	 * so, we must acquire a lock on the item to verify the id != 0.
	 * also, with hash not changed, we are using the right slab.
	 */
	lock_rw_rdlock(&key->entry.lock);
	if(key->id == id && key->entry.hash == hash) {
		lru_touch(table, &key->entry);
	}
	lock_rw_unlock(&key->entry.lock);
	lock_quick_unlock(&table->lock);
}