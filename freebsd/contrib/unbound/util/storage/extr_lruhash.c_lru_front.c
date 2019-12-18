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
struct lruhash_entry {struct lruhash_entry* lru_prev; struct lruhash_entry* lru_next; } ;
struct lruhash {struct lruhash_entry* lru_start; struct lruhash_entry* lru_end; } ;

/* Variables and functions */

void 
lru_front(struct lruhash* table, struct lruhash_entry* entry)
{
	entry->lru_prev = NULL;
	entry->lru_next = table->lru_start;
	if(!table->lru_start)
		table->lru_end = entry;
	else	table->lru_start->lru_prev = entry;
	table->lru_start = entry;
}