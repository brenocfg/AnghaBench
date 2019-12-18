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
struct slabhash {size_t size; TYPE_1__** array; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ space_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 

size_t slabhash_get_size(struct slabhash* sl)
{
	size_t i, total = 0;
	for(i=0; i<sl->size; i++) {
		lock_quick_lock(&sl->array[i]->lock);
		total += sl->array[i]->space_max;
		lock_quick_unlock(&sl->array[i]->lock);
	}
	return total;
}