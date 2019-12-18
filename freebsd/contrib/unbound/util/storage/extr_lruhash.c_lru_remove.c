#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lruhash_entry {TYPE_2__* lru_prev; TYPE_1__* lru_next; } ;
struct lruhash {TYPE_2__* lru_end; TYPE_1__* lru_start; } ;
struct TYPE_4__ {TYPE_1__* lru_next; } ;
struct TYPE_3__ {TYPE_2__* lru_prev; } ;

/* Variables and functions */

void 
lru_remove(struct lruhash* table, struct lruhash_entry* entry)
{
	if(entry->lru_prev)
		entry->lru_prev->lru_next = entry->lru_next;
	else	table->lru_start = entry->lru_next;
	if(entry->lru_next)
		entry->lru_next->lru_prev = entry->lru_prev;
	else	table->lru_end = entry->lru_prev;
}