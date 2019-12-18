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
struct lruhash_entry {int /*<<< orphan*/  lock; } ;
struct lruhash_bin {int /*<<< orphan*/  lock; } ;
struct lruhash {size_t size_mask; int /*<<< orphan*/  lock; struct lruhash_bin* array; int /*<<< orphan*/  compfunc; } ;
typedef  size_t hashvalue_type ;

/* Variables and functions */
 struct lruhash_entry* bin_find_entry (struct lruhash*,struct lruhash_bin*,size_t,void*) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_hash_compfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_touch (struct lruhash*,struct lruhash_entry*) ; 

struct lruhash_entry* 
lruhash_lookup(struct lruhash* table, hashvalue_type hash, void* key, int wr)
{
	struct lruhash_entry* entry;
	struct lruhash_bin* bin;
	fptr_ok(fptr_whitelist_hash_compfunc(table->compfunc));

	lock_quick_lock(&table->lock);
	bin = &table->array[hash & table->size_mask];
	lock_quick_lock(&bin->lock);
	if((entry=bin_find_entry(table, bin, hash, key)))
		lru_touch(table, entry);
	lock_quick_unlock(&table->lock);

	if(entry) {
		if(wr)	{ lock_rw_wrlock(&entry->lock); }
		else	{ lock_rw_rdlock(&entry->lock); }
	}
	lock_quick_unlock(&bin->lock);
	return entry;
}