#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int u_int ;
struct TYPE_4__ {int busy_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int VPB_BIT_WAITERS ; 
 int VPB_SHARERS (int) ; 
 int VPB_SHARERS_WORD (int) ; 
 int VPB_SINGLE_EXCLUSIVER ; 
 int /*<<< orphan*/  atomic_fcmpset_acq_int (int*,int*,int) ; 
 int /*<<< orphan*/  vm_page_assert_sbusied (TYPE_1__*) ; 

int
vm_page_busy_tryupgrade(vm_page_t m)
{
	u_int x;

	vm_page_assert_sbusied(m);

	x = m->busy_lock;
	for (;;) {
		if (VPB_SHARERS(x) > 1)
			return (0);
		KASSERT((x & ~VPB_BIT_WAITERS) == VPB_SHARERS_WORD(1),
		    ("vm_page_busy_tryupgrade: invalid lock state"));
		if (!atomic_fcmpset_acq_int(&m->busy_lock, &x,
		    VPB_SINGLE_EXCLUSIVER | (x & VPB_BIT_WAITERS)))
			continue;
		return (1);
	}
}