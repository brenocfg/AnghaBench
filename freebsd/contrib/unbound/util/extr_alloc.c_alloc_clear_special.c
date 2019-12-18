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
struct alloc_cache {int /*<<< orphan*/  lock; int /*<<< orphan*/  super; scalar_t__ num_quar; scalar_t__ quar; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_clear_special_list (struct alloc_cache*) ; 
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 

void
alloc_clear_special(struct alloc_cache* alloc)
{
	if(!alloc->super) {
		lock_quick_lock(&alloc->lock);
	}
	alloc_clear_special_list(alloc);
	alloc->quar = 0;
	alloc->num_quar = 0;
	if(!alloc->super) {
		lock_quick_unlock(&alloc->lock);
	}
}