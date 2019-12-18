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
struct alloc_cache {scalar_t__ num_quar; int /*<<< orphan*/  lock; scalar_t__ super; int /*<<< orphan*/ * quar; } ;
typedef  int /*<<< orphan*/  alloc_special_type ;

/* Variables and functions */
 scalar_t__ ALLOC_SPECIAL_MAX ; 
 int /*<<< orphan*/  alloc_set_special_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_special_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (struct alloc_cache*) ; 
 int /*<<< orphan*/  pushintosuper (struct alloc_cache*,int /*<<< orphan*/ *) ; 

void 
alloc_special_release(struct alloc_cache* alloc, alloc_special_type* mem)
{
	log_assert(alloc);
	if(!mem)
		return;
	if(!alloc->super) { 
		lock_quick_lock(&alloc->lock); /* superalloc needs locking */
	}

	alloc_special_clean(mem);
	if(alloc->super && alloc->num_quar >= ALLOC_SPECIAL_MAX) {
		/* push it to the super structure */
		pushintosuper(alloc, mem);
		return;
	}

	alloc_set_special_next(mem, alloc->quar);
	alloc->quar = mem;
	alloc->num_quar++;
	if(!alloc->super) {
		lock_quick_unlock(&alloc->lock);
	}
}