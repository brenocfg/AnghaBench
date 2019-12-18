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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
struct netmap_mem_d {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* nmd_ofstophys ) (struct netmap_mem_d*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NMA_LOCK (struct netmap_mem_d*) ; 
 int /*<<< orphan*/  NMA_SPINLOCK (struct netmap_mem_d*) ; 
 int /*<<< orphan*/  NMA_UNLOCK (struct netmap_mem_d*) ; 
 int /*<<< orphan*/  stub1 (struct netmap_mem_d*,int /*<<< orphan*/ ) ; 

vm_paddr_t
netmap_mem_ofstophys(struct netmap_mem_d *nmd, vm_ooffset_t off)
{
	vm_paddr_t pa;

#if defined(__FreeBSD__)
	/* This function is called by netmap_dev_pager_fault(), which holds a
	 * non-sleepable lock since FreeBSD 12. Since we cannot sleep, we
	 * spin on the trylock. */
	NMA_SPINLOCK(nmd);
#else
	NMA_LOCK(nmd);
#endif
	pa = nmd->ops->nmd_ofstophys(nmd, off);
	NMA_UNLOCK(nmd);

	return pa;
}