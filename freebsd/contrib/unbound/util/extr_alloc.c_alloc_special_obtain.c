#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct alloc_cache {TYPE_1__* super; int /*<<< orphan*/  num_quar; TYPE_2__* quar; } ;
struct TYPE_7__ {void* id; } ;
typedef  TYPE_2__ alloc_special_type ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  num_quar; TYPE_2__* quar; } ;

/* Variables and functions */
 void* alloc_get_id (struct alloc_cache*) ; 
 int /*<<< orphan*/  alloc_setup_special (TYPE_2__*) ; 
 void* alloc_special_next (TYPE_2__*) ; 
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (struct alloc_cache*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  prealloc_setup (struct alloc_cache*) ; 

alloc_special_type* 
alloc_special_obtain(struct alloc_cache* alloc)
{
	alloc_special_type* p;
	log_assert(alloc);
	/* see if in local cache */
	if(alloc->quar) {
		p = alloc->quar;
		alloc->quar = alloc_special_next(p);
		alloc->num_quar--;
		p->id = alloc_get_id(alloc);
		return p;
	}
	/* see if in global cache */
	if(alloc->super) {
		/* could maybe grab alloc_max/2 entries in one go,
		 * but really, isn't that just as fast as this code? */
		lock_quick_lock(&alloc->super->lock);
		if((p = alloc->super->quar)) {
			alloc->super->quar = alloc_special_next(p);
			alloc->super->num_quar--;
		}
		lock_quick_unlock(&alloc->super->lock);
		if(p) {
			p->id = alloc_get_id(alloc);
			return p;
		}
	}
	/* allocate new */
	prealloc_setup(alloc);
	if(!(p = (alloc_special_type*)malloc(sizeof(alloc_special_type)))) {
		log_err("alloc_special_obtain: out of memory");
		return NULL;
	}
	alloc_setup_special(p);
	p->id = alloc_get_id(alloc);
	return p;
}