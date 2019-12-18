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
struct bit_map {int used; int first_free; int /*<<< orphan*/  lock; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

void bit_map_clear(struct bit_map *t, int offset, int len)
{
	int i;

	if (t->used < len)
		BUG();		/* Much too late to do any good, but alas... */
	spin_lock(&t->lock);
	for (i = 0; i < len; i++) {
		if (test_bit(offset + i, t->map) == 0)
			BUG();
		__clear_bit(offset + i, t->map);
	}
	if (offset < t->first_free)
		t->first_free = offset;
	t->used -= len;
	spin_unlock(&t->lock);
}