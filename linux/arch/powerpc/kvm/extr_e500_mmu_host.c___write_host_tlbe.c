#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned long uint32_t ;
typedef  unsigned long u32 ;
struct kvm_book3e_206_tlb_entry {unsigned long mas1; int mas7_3; scalar_t__ mas2; int /*<<< orphan*/  mas8; } ;

/* Variables and functions */
 unsigned long MAS8_TGS ; 
 int /*<<< orphan*/  SPRN_MAS0 ; 
 int /*<<< orphan*/  SPRN_MAS1 ; 
 int /*<<< orphan*/  SPRN_MAS2 ; 
 int /*<<< orphan*/  SPRN_MAS3 ; 
 int /*<<< orphan*/  SPRN_MAS7 ; 
 int /*<<< orphan*/  SPRN_MAS8 ; 
 unsigned long get_thread_specific_lpid (unsigned long) ; 
 int /*<<< orphan*/  isync () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  trace_kvm_booke206_stlb_write (unsigned long,int /*<<< orphan*/ ,unsigned long,scalar_t__,int) ; 

__attribute__((used)) static inline void __write_host_tlbe(struct kvm_book3e_206_tlb_entry *stlbe,
				     uint32_t mas0,
				     uint32_t lpid)
{
	unsigned long flags;

	local_irq_save(flags);
	mtspr(SPRN_MAS0, mas0);
	mtspr(SPRN_MAS1, stlbe->mas1);
	mtspr(SPRN_MAS2, (unsigned long)stlbe->mas2);
	mtspr(SPRN_MAS3, (u32)stlbe->mas7_3);
	mtspr(SPRN_MAS7, (u32)(stlbe->mas7_3 >> 32));
#ifdef CONFIG_KVM_BOOKE_HV
	mtspr(SPRN_MAS8, MAS8_TGS | get_thread_specific_lpid(lpid));
#endif
	asm volatile("isync; tlbwe" : : : "memory");

#ifdef CONFIG_KVM_BOOKE_HV
	/* Must clear mas8 for other host tlbwe's */
	mtspr(SPRN_MAS8, 0);
	isync();
#endif
	local_irq_restore(flags);

	trace_kvm_booke206_stlb_write(mas0, stlbe->mas8, stlbe->mas1,
	                              stlbe->mas2, stlbe->mas7_3);
}