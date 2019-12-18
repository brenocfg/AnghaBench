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
struct mips_coproc {int dummy; } ;
struct TYPE_2__ {long count_ctl; long count_hz; int /*<<< orphan*/  count_resume; struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_one_reg {int id; } ;
typedef  long s64 ;

/* Variables and functions */
 int EINVAL ; 
#define  KVM_REG_MIPS_COUNT_CTL 162 
#define  KVM_REG_MIPS_COUNT_HZ 161 
#define  KVM_REG_MIPS_COUNT_RESUME 160 
#define  KVM_REG_MIPS_CP0_BADVADDR 159 
#define  KVM_REG_MIPS_CP0_CAUSE 158 
#define  KVM_REG_MIPS_CP0_COMPARE 157 
#define  KVM_REG_MIPS_CP0_CONFIG 156 
#define  KVM_REG_MIPS_CP0_CONFIG1 155 
#define  KVM_REG_MIPS_CP0_CONFIG2 154 
#define  KVM_REG_MIPS_CP0_CONFIG3 153 
#define  KVM_REG_MIPS_CP0_CONFIG4 152 
#define  KVM_REG_MIPS_CP0_CONFIG5 151 
#define  KVM_REG_MIPS_CP0_CONFIG7 150 
#define  KVM_REG_MIPS_CP0_CONTEXT 149 
#define  KVM_REG_MIPS_CP0_COUNT 148 
#define  KVM_REG_MIPS_CP0_EBASE 147 
#define  KVM_REG_MIPS_CP0_ENTRYHI 146 
#define  KVM_REG_MIPS_CP0_ENTRYLO0 145 
#define  KVM_REG_MIPS_CP0_ENTRYLO1 144 
#define  KVM_REG_MIPS_CP0_EPC 143 
#define  KVM_REG_MIPS_CP0_ERROREPC 142 
#define  KVM_REG_MIPS_CP0_HWRENA 141 
#define  KVM_REG_MIPS_CP0_INDEX 140 
#define  KVM_REG_MIPS_CP0_INTCTL 139 
#define  KVM_REG_MIPS_CP0_KSCRATCH1 138 
#define  KVM_REG_MIPS_CP0_KSCRATCH2 137 
#define  KVM_REG_MIPS_CP0_KSCRATCH3 136 
#define  KVM_REG_MIPS_CP0_KSCRATCH4 135 
#define  KVM_REG_MIPS_CP0_KSCRATCH5 134 
#define  KVM_REG_MIPS_CP0_KSCRATCH6 133 
#define  KVM_REG_MIPS_CP0_PAGEMASK 132 
#define  KVM_REG_MIPS_CP0_PRID 131 
#define  KVM_REG_MIPS_CP0_STATUS 130 
#define  KVM_REG_MIPS_CP0_USERLOCAL 129 
#define  KVM_REG_MIPS_CP0_WIRED 128 
 long ktime_to_ns (int /*<<< orphan*/ ) ; 
 long kvm_mips_read_count (struct kvm_vcpu*) ; 
 scalar_t__ kvm_read_c0_guest_badvaddr (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_cause (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_compare (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_config (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_config1 (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_config2 (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_config3 (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_config4 (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_config5 (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_config7 (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_context (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_ebase (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_entryhi (struct mips_coproc*) ; 
 long kvm_read_c0_guest_entrylo0 (struct mips_coproc*) ; 
 long kvm_read_c0_guest_entrylo1 (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_epc (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_errorepc (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_hwrena (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_index (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_intctl (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_kscratch1 (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_kscratch2 (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_kscratch3 (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_kscratch4 (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_kscratch5 (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_kscratch6 (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_pagemask (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_prid (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_status (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_userlocal (struct mips_coproc*) ; 
 scalar_t__ kvm_read_c0_guest_wired (struct mips_coproc*) ; 

__attribute__((used)) static int kvm_trap_emul_get_one_reg(struct kvm_vcpu *vcpu,
				     const struct kvm_one_reg *reg,
				     s64 *v)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;

	switch (reg->id) {
	case KVM_REG_MIPS_CP0_INDEX:
		*v = (long)kvm_read_c0_guest_index(cop0);
		break;
	case KVM_REG_MIPS_CP0_ENTRYLO0:
		*v = kvm_read_c0_guest_entrylo0(cop0);
		break;
	case KVM_REG_MIPS_CP0_ENTRYLO1:
		*v = kvm_read_c0_guest_entrylo1(cop0);
		break;
	case KVM_REG_MIPS_CP0_CONTEXT:
		*v = (long)kvm_read_c0_guest_context(cop0);
		break;
	case KVM_REG_MIPS_CP0_USERLOCAL:
		*v = (long)kvm_read_c0_guest_userlocal(cop0);
		break;
	case KVM_REG_MIPS_CP0_PAGEMASK:
		*v = (long)kvm_read_c0_guest_pagemask(cop0);
		break;
	case KVM_REG_MIPS_CP0_WIRED:
		*v = (long)kvm_read_c0_guest_wired(cop0);
		break;
	case KVM_REG_MIPS_CP0_HWRENA:
		*v = (long)kvm_read_c0_guest_hwrena(cop0);
		break;
	case KVM_REG_MIPS_CP0_BADVADDR:
		*v = (long)kvm_read_c0_guest_badvaddr(cop0);
		break;
	case KVM_REG_MIPS_CP0_ENTRYHI:
		*v = (long)kvm_read_c0_guest_entryhi(cop0);
		break;
	case KVM_REG_MIPS_CP0_COMPARE:
		*v = (long)kvm_read_c0_guest_compare(cop0);
		break;
	case KVM_REG_MIPS_CP0_STATUS:
		*v = (long)kvm_read_c0_guest_status(cop0);
		break;
	case KVM_REG_MIPS_CP0_INTCTL:
		*v = (long)kvm_read_c0_guest_intctl(cop0);
		break;
	case KVM_REG_MIPS_CP0_CAUSE:
		*v = (long)kvm_read_c0_guest_cause(cop0);
		break;
	case KVM_REG_MIPS_CP0_EPC:
		*v = (long)kvm_read_c0_guest_epc(cop0);
		break;
	case KVM_REG_MIPS_CP0_PRID:
		*v = (long)kvm_read_c0_guest_prid(cop0);
		break;
	case KVM_REG_MIPS_CP0_EBASE:
		*v = (long)kvm_read_c0_guest_ebase(cop0);
		break;
	case KVM_REG_MIPS_CP0_CONFIG:
		*v = (long)kvm_read_c0_guest_config(cop0);
		break;
	case KVM_REG_MIPS_CP0_CONFIG1:
		*v = (long)kvm_read_c0_guest_config1(cop0);
		break;
	case KVM_REG_MIPS_CP0_CONFIG2:
		*v = (long)kvm_read_c0_guest_config2(cop0);
		break;
	case KVM_REG_MIPS_CP0_CONFIG3:
		*v = (long)kvm_read_c0_guest_config3(cop0);
		break;
	case KVM_REG_MIPS_CP0_CONFIG4:
		*v = (long)kvm_read_c0_guest_config4(cop0);
		break;
	case KVM_REG_MIPS_CP0_CONFIG5:
		*v = (long)kvm_read_c0_guest_config5(cop0);
		break;
	case KVM_REG_MIPS_CP0_CONFIG7:
		*v = (long)kvm_read_c0_guest_config7(cop0);
		break;
	case KVM_REG_MIPS_CP0_COUNT:
		*v = kvm_mips_read_count(vcpu);
		break;
	case KVM_REG_MIPS_COUNT_CTL:
		*v = vcpu->arch.count_ctl;
		break;
	case KVM_REG_MIPS_COUNT_RESUME:
		*v = ktime_to_ns(vcpu->arch.count_resume);
		break;
	case KVM_REG_MIPS_COUNT_HZ:
		*v = vcpu->arch.count_hz;
		break;
	case KVM_REG_MIPS_CP0_ERROREPC:
		*v = (long)kvm_read_c0_guest_errorepc(cop0);
		break;
	case KVM_REG_MIPS_CP0_KSCRATCH1:
		*v = (long)kvm_read_c0_guest_kscratch1(cop0);
		break;
	case KVM_REG_MIPS_CP0_KSCRATCH2:
		*v = (long)kvm_read_c0_guest_kscratch2(cop0);
		break;
	case KVM_REG_MIPS_CP0_KSCRATCH3:
		*v = (long)kvm_read_c0_guest_kscratch3(cop0);
		break;
	case KVM_REG_MIPS_CP0_KSCRATCH4:
		*v = (long)kvm_read_c0_guest_kscratch4(cop0);
		break;
	case KVM_REG_MIPS_CP0_KSCRATCH5:
		*v = (long)kvm_read_c0_guest_kscratch5(cop0);
		break;
	case KVM_REG_MIPS_CP0_KSCRATCH6:
		*v = (long)kvm_read_c0_guest_kscratch6(cop0);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}