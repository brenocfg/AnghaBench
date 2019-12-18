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
struct ib_pd {TYPE_1__* device; int /*<<< orphan*/  usecnt; int /*<<< orphan*/ * __internal_mr; } ;
struct TYPE_2__ {int (* dereg_mr ) (int /*<<< orphan*/ *) ;int (* dealloc_pd ) (struct ib_pd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int stub2 (struct ib_pd*) ; 

void ib_dealloc_pd(struct ib_pd *pd)
{
	int ret;

	if (pd->__internal_mr) {
		ret = pd->device->dereg_mr(pd->__internal_mr);
		WARN_ON(ret);
		pd->__internal_mr = NULL;
	}

	/* uverbs manipulates usecnt with proper locking, while the kabi
	   requires the caller to guarantee we can't race here. */
	WARN_ON(atomic_read(&pd->usecnt));

	/* Making delalloc_pd a void return is a WIP, no driver should return
	   an error here. */
	ret = pd->device->dealloc_pd(pd);
	WARN_ONCE(ret, "Infiniband HW driver failed dealloc_pd");
}