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
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_4__ {int oflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PTE_REF ; 
 int VPO_UNMANAGED ; 
 int moea_clear_bit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

int
moea_ts_referenced(mmu_t mmu, vm_page_t m)
{
	int count;

	KASSERT((m->oflags & VPO_UNMANAGED) == 0,
	    ("moea_ts_referenced: page %p is not managed", m));
	rw_wlock(&pvh_global_lock);
	count = moea_clear_bit(m, PTE_REF);
	rw_wunlock(&pvh_global_lock);
	return (count);
}