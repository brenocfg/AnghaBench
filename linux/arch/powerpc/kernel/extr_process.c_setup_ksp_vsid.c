#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long ksp_vsid; } ;
struct task_struct {TYPE_1__ thread; } ;
struct TYPE_4__ {unsigned long sllp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_FTR_1T_SEGMENT ; 
 int /*<<< orphan*/  MMU_SEGSIZE_1T ; 
 int /*<<< orphan*/  MMU_SEGSIZE_256M ; 
 unsigned long SLB_VSID_KERNEL ; 
 unsigned long SLB_VSID_SHIFT ; 
 unsigned long SLB_VSID_SHIFT_1T ; 
 unsigned long get_kernel_vsid (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ mmu_has_feature (int /*<<< orphan*/ ) ; 
 size_t mmu_linear_psize ; 
 TYPE_2__* mmu_psize_defs ; 
 scalar_t__ radix_enabled () ; 

__attribute__((used)) static void setup_ksp_vsid(struct task_struct *p, unsigned long sp)
{
#ifdef CONFIG_PPC_BOOK3S_64
	unsigned long sp_vsid;
	unsigned long llp = mmu_psize_defs[mmu_linear_psize].sllp;

	if (radix_enabled())
		return;

	if (mmu_has_feature(MMU_FTR_1T_SEGMENT))
		sp_vsid = get_kernel_vsid(sp, MMU_SEGSIZE_1T)
			<< SLB_VSID_SHIFT_1T;
	else
		sp_vsid = get_kernel_vsid(sp, MMU_SEGSIZE_256M)
			<< SLB_VSID_SHIFT;
	sp_vsid |= SLB_VSID_KERNEL | llp;
	p->thread.ksp_vsid = sp_vsid;
#endif
}