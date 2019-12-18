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
typedef  int u64 ;
struct copro_slb {int vsid; unsigned long esid; } ;
struct TYPE_2__ {int sllp; } ;

/* Variables and functions */
 unsigned long ESID_MASK ; 
 scalar_t__ LINEAR_MAP_REGION_ID ; 
 int /*<<< orphan*/  MMU_SEGSIZE_256M ; 
 unsigned long SLB_ESID_V ; 
 int SLB_VSID_KERNEL ; 
 int SLB_VSID_SHIFT ; 
 int get_kernel_vsid (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ get_region_id (unsigned long) ; 
 size_t mmu_linear_psize ; 
 TYPE_1__* mmu_psize_defs ; 
 size_t mmu_virtual_psize ; 

__attribute__((used)) static void __spu_kernel_slb(void *addr, struct copro_slb *slb)
{
	unsigned long ea = (unsigned long)addr;
	u64 llp;

	if (get_region_id(ea) == LINEAR_MAP_REGION_ID)
		llp = mmu_psize_defs[mmu_linear_psize].sllp;
	else
		llp = mmu_psize_defs[mmu_virtual_psize].sllp;

	slb->vsid = (get_kernel_vsid(ea, MMU_SEGSIZE_256M) << SLB_VSID_SHIFT) |
		SLB_VSID_KERNEL | llp;
	slb->esid = (ea & ESID_MASK) | SLB_ESID_V;
}