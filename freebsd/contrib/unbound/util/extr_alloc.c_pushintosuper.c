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
struct alloc_cache {int num_quar; TYPE_1__* super; int /*<<< orphan*/ * quar; } ;
typedef  int /*<<< orphan*/  alloc_special_type ;
struct TYPE_2__ {int num_quar; int /*<<< orphan*/  lock; int /*<<< orphan*/ * quar; } ;

/* Variables and functions */
 int ALLOC_SPECIAL_MAX ; 
 int /*<<< orphan*/  alloc_set_special_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* alloc_special_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int) ; 

__attribute__((used)) static void 
pushintosuper(struct alloc_cache* alloc, alloc_special_type* mem)
{
	int i;
	alloc_special_type *p = alloc->quar;
	log_assert(p);
	log_assert(alloc && alloc->super && 
		alloc->num_quar >= ALLOC_SPECIAL_MAX);
	/* push ALLOC_SPECIAL_MAX/2 after mem */
	alloc_set_special_next(mem, alloc->quar);
	for(i=1; i<ALLOC_SPECIAL_MAX/2; i++) {
		p = alloc_special_next(p);
	}
	alloc->quar = alloc_special_next(p);
	alloc->num_quar -= ALLOC_SPECIAL_MAX/2;

	/* dump mem+list into the super quar list */
	lock_quick_lock(&alloc->super->lock);
	alloc_set_special_next(p, alloc->super->quar);
	alloc->super->quar = mem;
	alloc->super->num_quar += ALLOC_SPECIAL_MAX/2 + 1;
	lock_quick_unlock(&alloc->super->lock);
	/* so 1 lock per mem+alloc/2 deletes */
}