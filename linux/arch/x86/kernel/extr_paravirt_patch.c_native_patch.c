#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  vcpu_is_preempted; int /*<<< orphan*/  queued_spin_unlock; } ;

/* Variables and functions */
 int PARAVIRT_PATCH (int /*<<< orphan*/ ) ; 
 unsigned int PATCH (TYPE_1__,int /*<<< orphan*/ ,void*,unsigned int) ; 
 int /*<<< orphan*/  PATCH_CASE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int) ; 
 int /*<<< orphan*/  cpu ; 
 int /*<<< orphan*/  iret ; 
 int /*<<< orphan*/  irq ; 
 int /*<<< orphan*/  irq_disable ; 
 int /*<<< orphan*/  irq_enable ; 
 TYPE_1__ lock ; 
 int /*<<< orphan*/  mmu ; 
 unsigned int paravirt_patch_default (int,void*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  pv_is_native_spin_unlock () ; 
 int /*<<< orphan*/  pv_is_native_vcpu_is_preempted () ; 
 int /*<<< orphan*/  queued_spin_unlock ; 
 int /*<<< orphan*/  read_cr2 ; 
 int /*<<< orphan*/  read_cr3 ; 
 int /*<<< orphan*/  restore_fl ; 
 int /*<<< orphan*/  save_fl ; 
 int /*<<< orphan*/  swapgs ; 
 int /*<<< orphan*/  usergs_sysret64 ; 
 int /*<<< orphan*/  vcpu_is_preempted ; 
 int /*<<< orphan*/  wbinvd ; 
 int /*<<< orphan*/  write_cr3 ; 
 int /*<<< orphan*/  xxl ; 

unsigned int native_patch(u8 type, void *insn_buff, unsigned long addr,
			  unsigned int len)
{
	switch (type) {

#ifdef CONFIG_PARAVIRT_XXL
	PATCH_CASE(irq, restore_fl, xxl, insn_buff, len);
	PATCH_CASE(irq, save_fl, xxl, insn_buff, len);
	PATCH_CASE(irq, irq_enable, xxl, insn_buff, len);
	PATCH_CASE(irq, irq_disable, xxl, insn_buff, len);

	PATCH_CASE(mmu, read_cr2, xxl, insn_buff, len);
	PATCH_CASE(mmu, read_cr3, xxl, insn_buff, len);
	PATCH_CASE(mmu, write_cr3, xxl, insn_buff, len);

# ifdef CONFIG_X86_64
	PATCH_CASE(cpu, usergs_sysret64, xxl, insn_buff, len);
	PATCH_CASE(cpu, swapgs, xxl, insn_buff, len);
	PATCH_CASE(cpu, wbinvd, xxl, insn_buff, len);
# else
	PATCH_CASE(cpu, iret, xxl, insn_buff, len);
# endif
#endif

#ifdef CONFIG_PARAVIRT_SPINLOCKS
	case PARAVIRT_PATCH(lock.queued_spin_unlock):
		if (pv_is_native_spin_unlock())
			return PATCH(lock, queued_spin_unlock, insn_buff, len);
		break;

	case PARAVIRT_PATCH(lock.vcpu_is_preempted):
		if (pv_is_native_vcpu_is_preempted())
			return PATCH(lock, vcpu_is_preempted, insn_buff, len);
		break;
#endif
	default:
		break;
	}

	return paravirt_patch_default(type, insn_buff, addr, len);
}