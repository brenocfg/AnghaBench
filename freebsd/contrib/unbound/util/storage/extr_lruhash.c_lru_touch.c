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
struct lruhash_entry {int dummy; } ;
struct lruhash {struct lruhash_entry* lru_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  lru_front (struct lruhash*,struct lruhash_entry*) ; 
 int /*<<< orphan*/  lru_remove (struct lruhash*,struct lruhash_entry*) ; 

void 
lru_touch(struct lruhash* table, struct lruhash_entry* entry)
{
	log_assert(table && entry);
	if(entry == table->lru_start)
		return; /* nothing to do */
	/* remove from current lru position */
	lru_remove(table, entry);
	/* add at front */
	lru_front(table, entry);
}