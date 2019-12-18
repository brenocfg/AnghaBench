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
struct lruhash_bin {int dummy; } ;
struct lruhash {int space_used; size_t size; int /*<<< orphan*/  lock; TYPE_1__* array; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t lock_get_mem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 

size_t
lruhash_get_mem(struct lruhash* table)
{
	size_t s;
	lock_quick_lock(&table->lock);
	s = sizeof(struct lruhash) + table->space_used;
#ifdef USE_THREAD_DEBUG
	if(table->size != 0) {
		size_t i;
		for(i=0; i<table->size; i++)
			s += sizeof(struct lruhash_bin) + 
				lock_get_mem(&table->array[i].lock);
	}
#else /* no THREAD_DEBUG */
	if(table->size != 0)
		s += (table->size)*(sizeof(struct lruhash_bin) + 
			lock_get_mem(&table->array[0].lock));
#endif
	lock_quick_unlock(&table->lock);
	s += lock_get_mem(&table->lock);
	return s;
}