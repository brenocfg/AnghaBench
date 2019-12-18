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
struct lruhash {size_t size; int /*<<< orphan*/  lock; scalar_t__ space_used; scalar_t__ num; int /*<<< orphan*/ * lru_end; int /*<<< orphan*/ * lru_start; int /*<<< orphan*/ * array; int /*<<< orphan*/  markdelfunc; int /*<<< orphan*/  deldatafunc; int /*<<< orphan*/  delkeyfunc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_clear (struct lruhash*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_hash_deldatafunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_hash_delkeyfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_hash_markdelfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 

void
lruhash_clear(struct lruhash* table)
{
	size_t i;
	if(!table)
		return;
	fptr_ok(fptr_whitelist_hash_delkeyfunc(table->delkeyfunc));
	fptr_ok(fptr_whitelist_hash_deldatafunc(table->deldatafunc));
	fptr_ok(fptr_whitelist_hash_markdelfunc(table->markdelfunc));

	lock_quick_lock(&table->lock);
	for(i=0; i<table->size; i++) {
		bin_clear(table, &table->array[i]);
	}
	table->lru_start = NULL;
	table->lru_end = NULL;
	table->num = 0;
	table->space_used = 0;
	lock_quick_unlock(&table->lock);
}