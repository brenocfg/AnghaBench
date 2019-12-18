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
struct lruhash_entry {int /*<<< orphan*/  key; void* data; struct lruhash_entry* overflow_next; int /*<<< orphan*/  lock; } ;
struct lruhash_bin {int /*<<< orphan*/  lock; struct lruhash_entry* overflow_list; } ;
struct lruhash {size_t (* sizefunc ) (int /*<<< orphan*/ ,void*) ;size_t size_mask; scalar_t__ num; scalar_t__ space_used; scalar_t__ space_max; scalar_t__ size; int /*<<< orphan*/  (* deldatafunc ) (void*,void*) ;int /*<<< orphan*/  (* delkeyfunc ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  lock; struct lruhash_bin* array; void* cb_arg; int /*<<< orphan*/  markdelfunc; int /*<<< orphan*/  compfunc; } ;
typedef  size_t hashvalue_type ;

/* Variables and functions */
 struct lruhash_entry* bin_find_entry (struct lruhash*,struct lruhash_bin*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_hash_compfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_hash_deldatafunc (int /*<<< orphan*/  (*) (void*,void*)) ; 
 int /*<<< orphan*/  fptr_whitelist_hash_delkeyfunc (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,void*)) ; 
 int /*<<< orphan*/  fptr_whitelist_hash_markdelfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_hash_sizefunc (size_t (*) (int /*<<< orphan*/ ,void*)) ; 
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_front (struct lruhash*,struct lruhash_entry*) ; 
 int /*<<< orphan*/  reclaim_space (struct lruhash*,struct lruhash_entry**) ; 
 size_t stub1 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub3 (void*,void*) ; 
 int /*<<< orphan*/  table_grow (struct lruhash*) ; 

struct lruhash_entry*
lruhash_insert_or_retrieve(struct lruhash* table, hashvalue_type hash,
	struct lruhash_entry* entry, void* data, void* cb_arg)
{
	struct lruhash_bin* bin;
	struct lruhash_entry* found, *reclaimlist = NULL;
	size_t need_size;
	fptr_ok(fptr_whitelist_hash_sizefunc(table->sizefunc));
	fptr_ok(fptr_whitelist_hash_delkeyfunc(table->delkeyfunc));
	fptr_ok(fptr_whitelist_hash_deldatafunc(table->deldatafunc));
	fptr_ok(fptr_whitelist_hash_compfunc(table->compfunc));
	fptr_ok(fptr_whitelist_hash_markdelfunc(table->markdelfunc));
	need_size = table->sizefunc(entry->key, data);
	if (cb_arg == NULL) cb_arg = table->cb_arg;

	/* find bin */
	lock_quick_lock(&table->lock);
	bin = &table->array[hash & table->size_mask];
	lock_quick_lock(&bin->lock);

	/* see if entry exists already */
	if ((found = bin_find_entry(table, bin, hash, entry->key)) != NULL) {
		/* if so: keep the existing data - acquire a writelock */
		lock_rw_wrlock(&found->lock);
	}
	else
	{
		/* if not: add to bin */
		entry->overflow_next = bin->overflow_list;
		bin->overflow_list = entry;
		lru_front(table, entry);
		table->num++;
		table->space_used += need_size;
		/* return the entry that was presented, and lock it */
		found = entry;
		lock_rw_wrlock(&found->lock);
	}
	lock_quick_unlock(&bin->lock);
	if (table->space_used > table->space_max)
		reclaim_space(table, &reclaimlist);
	if (table->num >= table->size)
		table_grow(table);
	lock_quick_unlock(&table->lock);

	/* finish reclaim if any (outside of critical region) */
	while (reclaimlist) {
		struct lruhash_entry* n = reclaimlist->overflow_next;
		void* d = reclaimlist->data;
		(*table->delkeyfunc)(reclaimlist->key, cb_arg);
		(*table->deldatafunc)(d, cb_arg);
		reclaimlist = n;
	}

	/* return the entry that was selected */
	return found;
}