#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {scalar_t__ (* is_dcbz32 ) (struct kvm_vcpu*) ;} ;
struct TYPE_6__ {int hflags; int pvr; TYPE_1__ mmu; int /*<<< orphan*/  cpu_type; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_8__ {int /*<<< orphan*/  platform; } ;
struct TYPE_7__ {int hior; int msr_mask; int /*<<< orphan*/  hior_explicit; } ;

/* Variables and functions */
 int BOOK3S_HFLAG_DCBZ32 ; 
 int BOOK3S_HFLAG_MULTI_PGSIZE ; 
 int BOOK3S_HFLAG_NATIVE_PS ; 
 int BOOK3S_HFLAG_NEW_TLBIE ; 
 int BOOK3S_HFLAG_SLB ; 
 int /*<<< orphan*/  KVM_CPU_3S_32 ; 
 int /*<<< orphan*/  KVM_CPU_3S_64 ; 
 int MSR_FE0 ; 
 int MSR_FE1 ; 
 int MSR_HV ; 
#define  PVR_POWER6 134 
#define  PVR_POWER7 133 
#define  PVR_POWER7p 132 
#define  PVR_POWER8 131 
#define  PVR_POWER8E 130 
#define  PVR_POWER8NVL 129 
#define  PVR_POWER9 128 
 int PVR_VER (int) ; 
 int /*<<< orphan*/  SPRN_HID2_GEKKO ; 
 TYPE_4__* cur_cpu_spec ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_32_init (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_init (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_sanity_check (struct kvm_vcpu*) ; 
 int mfmsr () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 
 TYPE_3__* to_book3s (struct kvm_vcpu*) ; 

void kvmppc_set_pvr_pr(struct kvm_vcpu *vcpu, u32 pvr)
{
	u32 host_pvr;

	vcpu->arch.hflags &= ~BOOK3S_HFLAG_SLB;
	vcpu->arch.pvr = pvr;
#ifdef CONFIG_PPC_BOOK3S_64
	if ((pvr >= 0x330000) && (pvr < 0x70330000)) {
		kvmppc_mmu_book3s_64_init(vcpu);
		if (!to_book3s(vcpu)->hior_explicit)
			to_book3s(vcpu)->hior = 0xfff00000;
		to_book3s(vcpu)->msr_mask = 0xffffffffffffffffULL;
		vcpu->arch.cpu_type = KVM_CPU_3S_64;
	} else
#endif
	{
		kvmppc_mmu_book3s_32_init(vcpu);
		if (!to_book3s(vcpu)->hior_explicit)
			to_book3s(vcpu)->hior = 0;
		to_book3s(vcpu)->msr_mask = 0xffffffffULL;
		vcpu->arch.cpu_type = KVM_CPU_3S_32;
	}

	kvmppc_sanity_check(vcpu);

	/* If we are in hypervisor level on 970, we can tell the CPU to
	 * treat DCBZ as 32 bytes store */
	vcpu->arch.hflags &= ~BOOK3S_HFLAG_DCBZ32;
	if (vcpu->arch.mmu.is_dcbz32(vcpu) && (mfmsr() & MSR_HV) &&
	    !strcmp(cur_cpu_spec->platform, "ppc970"))
		vcpu->arch.hflags |= BOOK3S_HFLAG_DCBZ32;

	/* Cell performs badly if MSR_FEx are set. So let's hope nobody
	   really needs them in a VM on Cell and force disable them. */
	if (!strcmp(cur_cpu_spec->platform, "ppc-cell-be"))
		to_book3s(vcpu)->msr_mask &= ~(MSR_FE0 | MSR_FE1);

	/*
	 * If they're asking for POWER6 or later, set the flag
	 * indicating that we can do multiple large page sizes
	 * and 1TB segments.
	 * Also set the flag that indicates that tlbie has the large
	 * page bit in the RB operand instead of the instruction.
	 */
	switch (PVR_VER(pvr)) {
	case PVR_POWER6:
	case PVR_POWER7:
	case PVR_POWER7p:
	case PVR_POWER8:
	case PVR_POWER8E:
	case PVR_POWER8NVL:
	case PVR_POWER9:
		vcpu->arch.hflags |= BOOK3S_HFLAG_MULTI_PGSIZE |
			BOOK3S_HFLAG_NEW_TLBIE;
		break;
	}

#ifdef CONFIG_PPC_BOOK3S_32
	/* 32 bit Book3S always has 32 byte dcbz */
	vcpu->arch.hflags |= BOOK3S_HFLAG_DCBZ32;
#endif

	/* On some CPUs we can execute paired single operations natively */
	asm ( "mfpvr %0" : "=r"(host_pvr));
	switch (host_pvr) {
	case 0x00080200:	/* lonestar 2.0 */
	case 0x00088202:	/* lonestar 2.2 */
	case 0x70000100:	/* gekko 1.0 */
	case 0x00080100:	/* gekko 2.0 */
	case 0x00083203:	/* gekko 2.3a */
	case 0x00083213:	/* gekko 2.3b */
	case 0x00083204:	/* gekko 2.4 */
	case 0x00083214:	/* gekko 2.4e (8SE) - retail HW2 */
	case 0x00087200:	/* broadway */
		vcpu->arch.hflags |= BOOK3S_HFLAG_NATIVE_PS;
		/* Enable HID2.PSE - in case we need it later */
		mtspr(SPRN_HID2_GEKKO, mfspr(SPRN_HID2_GEKKO) | (1 << 29));
	}
}