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
struct lruhash_entry {struct lruhash_entry* overflow_next; } ;
struct lruhash {int num; int space_used; size_t size; int size_mask; int /*<<< orphan*/  lock; TYPE_1__* array; scalar_t__ space_max; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct lruhash_entry* overflow_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_info (char*,...) ; 

void 
lruhash_status(struct lruhash* table, const char* id, int extended)
{
	lock_quick_lock(&table->lock);
	log_info("%s: %u entries, memory %u / %u",
		id, (unsigned)table->num, (unsigned)table->space_used,
		(unsigned)table->space_max);
	log_info("  itemsize %u, array %u, mask %d",
		(unsigned)(table->num? table->space_used/table->num : 0),
		(unsigned)table->size, table->size_mask);
	if(extended) {
		size_t i;
		int min=(int)table->size*2, max=-2;
		for(i=0; i<table->size; i++) {
			int here = 0;
			struct lruhash_entry *en;
			lock_quick_lock(&table->array[i].lock);
			en = table->array[i].overflow_list;
			while(en) {
				here ++;
				en = en->overflow_next;
			}
			lock_quick_unlock(&table->array[i].lock);
			if(extended >= 2)
				log_info("bin[%d] %d", (int)i, here);
			if(here > max) max = here;
			if(here < min) min = here;
		}
		log_info("  bin min %d, avg %.2lf, max %d", min, 
			(double)table->num/(double)table->size, max);
	}
	lock_quick_unlock(&table->lock);
}