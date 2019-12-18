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
struct lruhash_bin {int /*<<< orphan*/  lock; } ;
struct lruhash {int size_mask; int size; struct lruhash_bin* array; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_init (struct lruhash_bin*,int) ; 
 int /*<<< orphan*/  bin_split (struct lruhash*,struct lruhash_bin*,int) ; 
 struct lruhash_bin* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct lruhash_bin*) ; 
 int /*<<< orphan*/  lock_protect (int /*<<< orphan*/ *,struct lruhash_bin*,int) ; 
 int /*<<< orphan*/  lock_quick_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_unprotect (int /*<<< orphan*/ *,struct lruhash_bin*) ; 
 int /*<<< orphan*/  log_err (char*) ; 

void 
table_grow(struct lruhash* table)
{
	struct lruhash_bin* newa;
	int newmask;
	size_t i;
	if(table->size_mask == (int)(((size_t)-1)>>1)) {
		log_err("hash array malloc: size_t too small");
		return;
	}
	/* try to allocate new array, if not fail */
	newa = calloc(table->size*2, sizeof(struct lruhash_bin));
	if(!newa) {
		log_err("hash grow: malloc failed");
		/* continue with smaller array. Though its slower. */
		return;
	}
	bin_init(newa, table->size*2);
	newmask = (table->size_mask << 1) | 1;
	bin_split(table, newa, newmask);
	/* delete the old bins */
	lock_unprotect(&table->lock, table->array);
	for(i=0; i<table->size; i++) {
		lock_quick_destroy(&table->array[i].lock);
	}
	free(table->array);
	
	table->size *= 2;
	table->size_mask = newmask;
	table->array = newa;
	lock_protect(&table->lock, table->array, 
		table->size*sizeof(struct lruhash_bin));
	return;
}