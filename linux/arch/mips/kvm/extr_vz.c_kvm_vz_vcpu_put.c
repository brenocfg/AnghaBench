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
struct mips_coproc {int /*<<< orphan*/ ** reg; } ;
struct TYPE_3__ {struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPSR6_WIRED_WIRED ; 
 int MIPS_CONF3_PW ; 
 size_t MIPS_CP0_GUESTCTL2 ; 
 size_t MIPS_CP0_GUESTCTL2_SEL ; 
 int PF_VCPU ; 
 int /*<<< orphan*/  clear_gc0_wired (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_guest_has_badinstr ; 
 scalar_t__ cpu_guest_has_badinstrp ; 
 scalar_t__ cpu_guest_has_conf1 ; 
 scalar_t__ cpu_guest_has_conf2 ; 
 scalar_t__ cpu_guest_has_conf3 ; 
 scalar_t__ cpu_guest_has_conf4 ; 
 scalar_t__ cpu_guest_has_conf5 ; 
 scalar_t__ cpu_guest_has_conf6 ; 
 scalar_t__ cpu_guest_has_conf7 ; 
 scalar_t__ cpu_guest_has_contextconfig ; 
 scalar_t__ cpu_guest_has_htw ; 
 scalar_t__ cpu_guest_has_kscr (int) ; 
 scalar_t__ cpu_guest_has_segments ; 
 scalar_t__ cpu_guest_has_userlocal ; 
 scalar_t__ cpu_has_guestctl2 ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  kvm_lose_fpu (struct kvm_vcpu*) ; 
 int kvm_read_sw_gc0_config3 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_badinstr (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_badinstrp (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_badvaddr (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_config (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_config1 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_config2 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_config3 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_config4 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_config5 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_config6 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_config7 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_context (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_contextconfig (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_entryhi (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_entrylo0 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_entrylo1 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_epc (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_errorepc (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_hwrena (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_index (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_intctl (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_kscratch1 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_kscratch2 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_kscratch3 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_kscratch4 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_kscratch5 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_kscratch6 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_pagegrain (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_pagemask (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_pwbase (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_pwctl (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_pwfield (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_pwsize (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_segctl0 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_segctl1 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_segctl2 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_status (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_userlocal (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_wired (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_xcontext (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_save_gc0_xcontextconfig (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_vz_read_gc0_ebase () ; 
 int /*<<< orphan*/  kvm_vz_save_timer (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vz_vcpu_save_wired (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_write_sw_gc0_ebase (struct mips_coproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_c0_guestctl2 () ; 

__attribute__((used)) static int kvm_vz_vcpu_put(struct kvm_vcpu *vcpu, int cpu)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;

	if (current->flags & PF_VCPU)
		kvm_vz_vcpu_save_wired(vcpu);

	kvm_lose_fpu(vcpu);

	kvm_save_gc0_index(cop0);
	kvm_save_gc0_entrylo0(cop0);
	kvm_save_gc0_entrylo1(cop0);
	kvm_save_gc0_context(cop0);
	if (cpu_guest_has_contextconfig)
		kvm_save_gc0_contextconfig(cop0);
#ifdef CONFIG_64BIT
	kvm_save_gc0_xcontext(cop0);
	if (cpu_guest_has_contextconfig)
		kvm_save_gc0_xcontextconfig(cop0);
#endif
	kvm_save_gc0_pagemask(cop0);
	kvm_save_gc0_pagegrain(cop0);
	kvm_save_gc0_wired(cop0);
	/* allow wired TLB entries to be overwritten */
	clear_gc0_wired(MIPSR6_WIRED_WIRED);
	kvm_save_gc0_hwrena(cop0);
	kvm_save_gc0_badvaddr(cop0);
	kvm_save_gc0_entryhi(cop0);
	kvm_save_gc0_status(cop0);
	kvm_save_gc0_intctl(cop0);
	kvm_save_gc0_epc(cop0);
	kvm_write_sw_gc0_ebase(cop0, kvm_vz_read_gc0_ebase());
	if (cpu_guest_has_userlocal)
		kvm_save_gc0_userlocal(cop0);

	/* only save implemented config registers */
	kvm_save_gc0_config(cop0);
	if (cpu_guest_has_conf1)
		kvm_save_gc0_config1(cop0);
	if (cpu_guest_has_conf2)
		kvm_save_gc0_config2(cop0);
	if (cpu_guest_has_conf3)
		kvm_save_gc0_config3(cop0);
	if (cpu_guest_has_conf4)
		kvm_save_gc0_config4(cop0);
	if (cpu_guest_has_conf5)
		kvm_save_gc0_config5(cop0);
	if (cpu_guest_has_conf6)
		kvm_save_gc0_config6(cop0);
	if (cpu_guest_has_conf7)
		kvm_save_gc0_config7(cop0);

	kvm_save_gc0_errorepc(cop0);

	/* save KScratch registers if enabled in guest */
	if (cpu_guest_has_conf4) {
		if (cpu_guest_has_kscr(2))
			kvm_save_gc0_kscratch1(cop0);
		if (cpu_guest_has_kscr(3))
			kvm_save_gc0_kscratch2(cop0);
		if (cpu_guest_has_kscr(4))
			kvm_save_gc0_kscratch3(cop0);
		if (cpu_guest_has_kscr(5))
			kvm_save_gc0_kscratch4(cop0);
		if (cpu_guest_has_kscr(6))
			kvm_save_gc0_kscratch5(cop0);
		if (cpu_guest_has_kscr(7))
			kvm_save_gc0_kscratch6(cop0);
	}

	if (cpu_guest_has_badinstr)
		kvm_save_gc0_badinstr(cop0);
	if (cpu_guest_has_badinstrp)
		kvm_save_gc0_badinstrp(cop0);

	if (cpu_guest_has_segments) {
		kvm_save_gc0_segctl0(cop0);
		kvm_save_gc0_segctl1(cop0);
		kvm_save_gc0_segctl2(cop0);
	}

	/* save HTW registers if enabled in guest */
	if (cpu_guest_has_htw &&
	    kvm_read_sw_gc0_config3(cop0) & MIPS_CONF3_PW) {
		kvm_save_gc0_pwbase(cop0);
		kvm_save_gc0_pwfield(cop0);
		kvm_save_gc0_pwsize(cop0);
		kvm_save_gc0_pwctl(cop0);
	}

	kvm_vz_save_timer(vcpu);

	/* save Root.GuestCtl2 in unused Guest guestctl2 register */
	if (cpu_has_guestctl2)
		cop0->reg[MIPS_CP0_GUESTCTL2][MIPS_CP0_GUESTCTL2_SEL] =
			read_c0_guestctl2();

	return 0;
}