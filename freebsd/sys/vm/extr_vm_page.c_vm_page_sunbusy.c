#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int u_int ;
struct TYPE_5__ {int busy_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int VPB_BIT_WAITERS ; 
 int VPB_ONE_SHARER ; 
 int VPB_SHARERS (int) ; 
 int VPB_SHARERS_WORD (int) ; 
 int /*<<< orphan*/  VPB_UNBUSIED ; 
 scalar_t__ atomic_fcmpset_int (int*,int*,int) ; 
 int /*<<< orphan*/  atomic_fcmpset_rel_int (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_assert_sbusied (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (TYPE_1__*) ; 

void
vm_page_sunbusy(vm_page_t m)
{
	u_int x;

	vm_page_assert_sbusied(m);

	x = m->busy_lock;
	for (;;) {
		if (VPB_SHARERS(x) > 1) {
			if (atomic_fcmpset_int(&m->busy_lock, &x,
			    x - VPB_ONE_SHARER))
				break;
			continue;
		}
		KASSERT((x & ~VPB_BIT_WAITERS) == VPB_SHARERS_WORD(1),
		    ("vm_page_sunbusy: invalid lock state"));
		if (!atomic_fcmpset_rel_int(&m->busy_lock, &x, VPB_UNBUSIED))
			continue;
		if ((x & VPB_BIT_WAITERS) == 0)
			break;
		wakeup(m);
		break;
	}
}