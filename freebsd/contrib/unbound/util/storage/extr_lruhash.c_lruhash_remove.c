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
struct lruhash_entry {int /*<<< orphan*/  key; void* data; int /*<<< orphan*/  lock; } ;
struct lruhash_bin {int /*<<< orphan*/  lock; } ;
struct lruhash {size_t size_mask; int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* deldatafunc ) (void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* delkeyfunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* markdelfunc ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  lock; scalar_t__ (* sizefunc ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  space_used; int /*<<< orphan*/  num; struct lruhash_bin* array; int /*<<< orphan*/  compfunc; } ;
typedef  size_t hashvalue_type ;

/* Variables and functions */
 struct lruhash_entry* bin_find_entry (struct lruhash*,struct lruhash_bin*,size_t,void*) ; 
 int /*<<< orphan*/  bin_overflow_remove (struct lruhash_bin*,struct lruhash_entry*) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_hash_compfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_hash_deldatafunc (int /*<<< orphan*/  (*) (void*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  fptr_whitelist_hash_delkeyfunc (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  fptr_whitelist_hash_markdelfunc (int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  fptr_whitelist_hash_sizefunc (scalar_t__ (*) (int /*<<< orphan*/ ,void*)) ; 
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_remove (struct lruhash*,struct lruhash_entry*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (void*,int /*<<< orphan*/ ) ; 

void 
lruhash_remove(struct lruhash* table, hashvalue_type hash, void* key)
{
	struct lruhash_entry* entry;
	struct lruhash_bin* bin;
	void *d;
	fptr_ok(fptr_whitelist_hash_sizefunc(table->sizefunc));
	fptr_ok(fptr_whitelist_hash_delkeyfunc(table->delkeyfunc));
	fptr_ok(fptr_whitelist_hash_deldatafunc(table->deldatafunc));
	fptr_ok(fptr_whitelist_hash_compfunc(table->compfunc));
	fptr_ok(fptr_whitelist_hash_markdelfunc(table->markdelfunc));

	lock_quick_lock(&table->lock);
	bin = &table->array[hash & table->size_mask];
	lock_quick_lock(&bin->lock);
	if((entry=bin_find_entry(table, bin, hash, key))) {
		bin_overflow_remove(bin, entry);
		lru_remove(table, entry);
	} else {
		lock_quick_unlock(&table->lock);
		lock_quick_unlock(&bin->lock);
		return;
	}
	table->num--;
	table->space_used -= (*table->sizefunc)(entry->key, entry->data);
	lock_quick_unlock(&table->lock);
	lock_rw_wrlock(&entry->lock);
	if(table->markdelfunc)
		(*table->markdelfunc)(entry->key);
	lock_rw_unlock(&entry->lock);
	lock_quick_unlock(&bin->lock);
	/* finish removal */
	d = entry->data;
	(*table->delkeyfunc)(entry->key, table->cb_arg);
	(*table->deldatafunc)(d, table->cb_arg);
}