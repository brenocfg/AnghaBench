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

/* Variables and functions */
 int /*<<< orphan*/  lock_protect (int /*<<< orphan*/ *,struct lruhash_bin*,int) ; 
 int /*<<< orphan*/  lock_quick_init (int /*<<< orphan*/ *) ; 

void
bin_init(struct lruhash_bin* array, size_t size)
{
	size_t i;
#ifdef THREADS_DISABLED
	(void)array;
#endif
	for(i=0; i<size; i++) {
		lock_quick_init(&array[i].lock);
		lock_protect(&array[i].lock, &array[i], 
			sizeof(struct lruhash_bin));
	}
}