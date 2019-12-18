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
 int VPB_BIT_WAITERS ; 
 int /*<<< orphan*/  VPB_SHARERS_WORD (int) ; 
 scalar_t__ atomic_fcmpset_rel_int (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_assert_xbusied (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (TYPE_1__*) ; 

void
vm_page_busy_downgrade(vm_page_t m)
{
	u_int x;

	vm_page_assert_xbusied(m);

	x = m->busy_lock;
	for (;;) {
		if (atomic_fcmpset_rel_int(&m->busy_lock,
		    &x, VPB_SHARERS_WORD(1)))
			break;
	}
	if ((x & VPB_BIT_WAITERS) != 0)
		wakeup(m);
}