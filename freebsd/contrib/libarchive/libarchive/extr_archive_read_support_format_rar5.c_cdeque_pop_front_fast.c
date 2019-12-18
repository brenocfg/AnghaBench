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
struct cdeque {size_t beg_pos; int cap_mask; int /*<<< orphan*/  size; scalar_t__* arr; } ;

/* Variables and functions */

__attribute__((used)) static void cdeque_pop_front_fast(struct cdeque* d, void** value) {
	*value = (void*) d->arr[d->beg_pos];
	d->beg_pos = (d->beg_pos + 1) & d->cap_mask;
	d->size--;
}