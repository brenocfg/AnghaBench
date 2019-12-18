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
typedef  int /*<<< orphan*/  u32 ;
struct mips_coproc {int dummy; } ;
struct TYPE_2__ {struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_one_reg {int id; } ;
typedef  unsigned int s64 ;

/* Variables and functions */
 unsigned int CAUSEF_DC ; 
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
 int MIPS_EBASE_CPUNUM ; 
 int /*<<< orphan*/  kvm_change_c0_guest_cause (struct mips_coproc*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kvm_change_c0_guest_ebase (struct mips_coproc*,int,unsigned int) ; 
 unsigned int kvm_mips_config1_wrmask (struct kvm_vcpu*) ; 
 unsigned int kvm_mips_config3_wrmask (struct kvm_vcpu*) ; 
 unsigned int kvm_mips_config4_wrmask (struct kvm_vcpu*) ; 
 unsigned int kvm_mips_config5_wrmask (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_count_disable_cause (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_count_enable_cause (struct kvm_vcpu*) ; 
 int kvm_mips_set_count_ctl (struct kvm_vcpu*,unsigned int) ; 
 int kvm_mips_set_count_hz (struct kvm_vcpu*,unsigned int) ; 
 int kvm_mips_set_count_resume (struct kvm_vcpu*,unsigned int) ; 
 int /*<<< orphan*/  kvm_mips_write_compare (struct kvm_vcpu*,unsigned int,int) ; 
 int /*<<< orphan*/  kvm_mips_write_count (struct kvm_vcpu*,unsigned int) ; 
 unsigned int kvm_read_c0_guest_cause (struct mips_coproc*) ; 
 unsigned int kvm_read_c0_guest_config1 (struct mips_coproc*) ; 
 unsigned int kvm_read_c0_guest_config3 (struct mips_coproc*) ; 
 unsigned int kvm_read_c0_guest_config4 (struct mips_coproc*) ; 
 unsigned int kvm_read_c0_guest_config5 (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_badvaddr (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_cause (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_config1 (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_config3 (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_config4 (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_config5 (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_context (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_entryhi (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_entrylo0 (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_entrylo1 (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_epc (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_errorepc (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_hwrena (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_index (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_kscratch1 (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_kscratch2 (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_kscratch3 (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_kscratch4 (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_kscratch5 (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_kscratch6 (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_pagemask (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_prid (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_status (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_userlocal (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_wired (struct mips_coproc*,unsigned int) ; 

__attribute__((used)) static int kvm_trap_emul_set_one_reg(struct kvm_vcpu *vcpu,
				     const struct kvm_one_reg *reg,
				     s64 v)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	int ret = 0;
	unsigned int cur, change;

	switch (reg->id) {
	case KVM_REG_MIPS_CP0_INDEX:
		kvm_write_c0_guest_index(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_ENTRYLO0:
		kvm_write_c0_guest_entrylo0(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_ENTRYLO1:
		kvm_write_c0_guest_entrylo1(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_CONTEXT:
		kvm_write_c0_guest_context(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_USERLOCAL:
		kvm_write_c0_guest_userlocal(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_PAGEMASK:
		kvm_write_c0_guest_pagemask(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_WIRED:
		kvm_write_c0_guest_wired(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_HWRENA:
		kvm_write_c0_guest_hwrena(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_BADVADDR:
		kvm_write_c0_guest_badvaddr(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_ENTRYHI:
		kvm_write_c0_guest_entryhi(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_STATUS:
		kvm_write_c0_guest_status(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_INTCTL:
		/* No VInt, so no VS, read-only for now */
		break;
	case KVM_REG_MIPS_CP0_EPC:
		kvm_write_c0_guest_epc(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_PRID:
		kvm_write_c0_guest_prid(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_EBASE:
		/*
		 * Allow core number to be written, but the exception base must
		 * remain in guest KSeg0.
		 */
		kvm_change_c0_guest_ebase(cop0, 0x1ffff000 | MIPS_EBASE_CPUNUM,
					  v);
		break;
	case KVM_REG_MIPS_CP0_COUNT:
		kvm_mips_write_count(vcpu, v);
		break;
	case KVM_REG_MIPS_CP0_COMPARE:
		kvm_mips_write_compare(vcpu, v, false);
		break;
	case KVM_REG_MIPS_CP0_CAUSE:
		/*
		 * If the timer is stopped or started (DC bit) it must look
		 * atomic with changes to the interrupt pending bits (TI, IRQ5).
		 * A timer interrupt should not happen in between.
		 */
		if ((kvm_read_c0_guest_cause(cop0) ^ v) & CAUSEF_DC) {
			if (v & CAUSEF_DC) {
				/* disable timer first */
				kvm_mips_count_disable_cause(vcpu);
				kvm_change_c0_guest_cause(cop0, (u32)~CAUSEF_DC,
							  v);
			} else {
				/* enable timer last */
				kvm_change_c0_guest_cause(cop0, (u32)~CAUSEF_DC,
							  v);
				kvm_mips_count_enable_cause(vcpu);
			}
		} else {
			kvm_write_c0_guest_cause(cop0, v);
		}
		break;
	case KVM_REG_MIPS_CP0_CONFIG:
		/* read-only for now */
		break;
	case KVM_REG_MIPS_CP0_CONFIG1:
		cur = kvm_read_c0_guest_config1(cop0);
		change = (cur ^ v) & kvm_mips_config1_wrmask(vcpu);
		if (change) {
			v = cur ^ change;
			kvm_write_c0_guest_config1(cop0, v);
		}
		break;
	case KVM_REG_MIPS_CP0_CONFIG2:
		/* read-only for now */
		break;
	case KVM_REG_MIPS_CP0_CONFIG3:
		cur = kvm_read_c0_guest_config3(cop0);
		change = (cur ^ v) & kvm_mips_config3_wrmask(vcpu);
		if (change) {
			v = cur ^ change;
			kvm_write_c0_guest_config3(cop0, v);
		}
		break;
	case KVM_REG_MIPS_CP0_CONFIG4:
		cur = kvm_read_c0_guest_config4(cop0);
		change = (cur ^ v) & kvm_mips_config4_wrmask(vcpu);
		if (change) {
			v = cur ^ change;
			kvm_write_c0_guest_config4(cop0, v);
		}
		break;
	case KVM_REG_MIPS_CP0_CONFIG5:
		cur = kvm_read_c0_guest_config5(cop0);
		change = (cur ^ v) & kvm_mips_config5_wrmask(vcpu);
		if (change) {
			v = cur ^ change;
			kvm_write_c0_guest_config5(cop0, v);
		}
		break;
	case KVM_REG_MIPS_CP0_CONFIG7:
		/* writes ignored */
		break;
	case KVM_REG_MIPS_COUNT_CTL:
		ret = kvm_mips_set_count_ctl(vcpu, v);
		break;
	case KVM_REG_MIPS_COUNT_RESUME:
		ret = kvm_mips_set_count_resume(vcpu, v);
		break;
	case KVM_REG_MIPS_COUNT_HZ:
		ret = kvm_mips_set_count_hz(vcpu, v);
		break;
	case KVM_REG_MIPS_CP0_ERROREPC:
		kvm_write_c0_guest_errorepc(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_KSCRATCH1:
		kvm_write_c0_guest_kscratch1(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_KSCRATCH2:
		kvm_write_c0_guest_kscratch2(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_KSCRATCH3:
		kvm_write_c0_guest_kscratch3(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_KSCRATCH4:
		kvm_write_c0_guest_kscratch4(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_KSCRATCH5:
		kvm_write_c0_guest_kscratch5(cop0, v);
		break;
	case KVM_REG_MIPS_CP0_KSCRATCH6:
		kvm_write_c0_guest_kscratch6(cop0, v);
		break;
	default:
		return -EINVAL;
	}
	return ret;
}