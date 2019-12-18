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
struct cdeque {int beg_pos; int end_pos; scalar_t__ cap_mask; int /*<<< orphan*/ * arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cdeque_free(struct cdeque* d) {
	if(!d)
		return;

	if(!d->arr)
		return;

	free(d->arr);

	d->arr = NULL;
	d->beg_pos = -1;
	d->end_pos = -1;
	d->cap_mask = 0;
}