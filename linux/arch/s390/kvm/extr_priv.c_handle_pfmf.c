#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_2__* sie_block; int /*<<< orphan*/  pgm; } ;
struct TYPE_14__ {int /*<<< orphan*/  instruction_pfmf; } ;
struct kvm_vcpu {TYPE_5__* run; TYPE_3__ arch; int /*<<< orphan*/  kvm; TYPE_1__ stat; } ;
struct TYPE_22__ {TYPE_10__* mm; } ;
struct TYPE_21__ {int mask; } ;
struct TYPE_20__ {scalar_t__ eaba; } ;
struct TYPE_17__ {int* gprs; } ;
struct TYPE_19__ {TYPE_4__ regs; } ;
struct TYPE_18__ {TYPE_6__ s; } ;
struct TYPE_15__ {TYPE_8__ gpsw; } ;
struct TYPE_13__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EFAULT ; 
 int /*<<< orphan*/  FAULT_FLAG_WRITE ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 int PFMF_CF ; 
 int PFMF_FSC ; 
 unsigned char PFMF_KEY ; 
 int PFMF_MC ; 
 int PFMF_MR ; 
 int PFMF_NQ ; 
 int PFMF_RESERVED ; 
 int PFMF_SK ; 
 int /*<<< orphan*/  PGM_ADDRESSING ; 
 int /*<<< orphan*/  PGM_OPERATION ; 
 int /*<<< orphan*/  PGM_PRIVILEGED_OP ; 
 int /*<<< orphan*/  PGM_SPECIFICATION ; 
 scalar_t__ PSW_BITS_AMODE_24BIT ; 
 scalar_t__ PSW_BITS_AMODE_64BIT ; 
 int PSW_MASK_PSTATE ; 
 int /*<<< orphan*/  _REGION3_SIZE ; 
 int /*<<< orphan*/  _SEGMENT_SIZE ; 
 int cond_set_guest_storage_key (TYPE_10__*,unsigned long,unsigned char,int /*<<< orphan*/ *,int,int,int) ; 
 TYPE_9__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int fixup_user_fault (TYPE_9__*,TYPE_10__*,unsigned long,int /*<<< orphan*/ ,int*) ; 
 unsigned long gfn_to_hva (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpa_to_gfn (unsigned long) ; 
 scalar_t__ kvm_clear_guest (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 scalar_t__ kvm_is_error_hva (unsigned long) ; 
 scalar_t__ kvm_s390_check_low_addr_prot_real (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  kvm_s390_get_regs_rre (struct kvm_vcpu*,int*,int*) ; 
 int kvm_s390_inject_prog_irq (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 unsigned long kvm_s390_logical_to_effective (struct kvm_vcpu*,unsigned long) ; 
 unsigned long kvm_s390_real_to_abs (struct kvm_vcpu*,unsigned long) ; 
 int kvm_s390_skey_check_enable (struct kvm_vcpu*) ; 
 TYPE_7__ psw_bits (TYPE_8__) ; 
 scalar_t__ test_kvm_facility (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_pfmf(struct kvm_vcpu *vcpu)
{
	bool mr = false, mc = false, nq;
	int reg1, reg2;
	unsigned long start, end;
	unsigned char key;

	vcpu->stat.instruction_pfmf++;

	kvm_s390_get_regs_rre(vcpu, &reg1, &reg2);

	if (!test_kvm_facility(vcpu->kvm, 8))
		return kvm_s390_inject_program_int(vcpu, PGM_OPERATION);

	if (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		return kvm_s390_inject_program_int(vcpu, PGM_PRIVILEGED_OP);

	if (vcpu->run->s.regs.gprs[reg1] & PFMF_RESERVED)
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

	/* Only provide non-quiescing support if enabled for the guest */
	if (vcpu->run->s.regs.gprs[reg1] & PFMF_NQ &&
	    !test_kvm_facility(vcpu->kvm, 14))
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

	/* Only provide conditional-SSKE support if enabled for the guest */
	if (vcpu->run->s.regs.gprs[reg1] & PFMF_SK &&
	    test_kvm_facility(vcpu->kvm, 10)) {
		mr = vcpu->run->s.regs.gprs[reg1] & PFMF_MR;
		mc = vcpu->run->s.regs.gprs[reg1] & PFMF_MC;
	}

	nq = vcpu->run->s.regs.gprs[reg1] & PFMF_NQ;
	key = vcpu->run->s.regs.gprs[reg1] & PFMF_KEY;
	start = vcpu->run->s.regs.gprs[reg2] & PAGE_MASK;
	start = kvm_s390_logical_to_effective(vcpu, start);

	if (vcpu->run->s.regs.gprs[reg1] & PFMF_CF) {
		if (kvm_s390_check_low_addr_prot_real(vcpu, start))
			return kvm_s390_inject_prog_irq(vcpu, &vcpu->arch.pgm);
	}

	switch (vcpu->run->s.regs.gprs[reg1] & PFMF_FSC) {
	case 0x00000000:
		/* only 4k frames specify a real address */
		start = kvm_s390_real_to_abs(vcpu, start);
		end = (start + PAGE_SIZE) & ~(PAGE_SIZE - 1);
		break;
	case 0x00001000:
		end = (start + _SEGMENT_SIZE) & ~(_SEGMENT_SIZE - 1);
		break;
	case 0x00002000:
		/* only support 2G frame size if EDAT2 is available and we are
		   not in 24-bit addressing mode */
		if (!test_kvm_facility(vcpu->kvm, 78) ||
		    psw_bits(vcpu->arch.sie_block->gpsw).eaba == PSW_BITS_AMODE_24BIT)
			return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);
		end = (start + _REGION3_SIZE) & ~(_REGION3_SIZE - 1);
		break;
	default:
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);
	}

	while (start != end) {
		unsigned long vmaddr;
		bool unlocked = false;

		/* Translate guest address to host address */
		vmaddr = gfn_to_hva(vcpu->kvm, gpa_to_gfn(start));
		if (kvm_is_error_hva(vmaddr))
			return kvm_s390_inject_program_int(vcpu, PGM_ADDRESSING);

		if (vcpu->run->s.regs.gprs[reg1] & PFMF_CF) {
			if (kvm_clear_guest(vcpu->kvm, start, PAGE_SIZE))
				return kvm_s390_inject_program_int(vcpu, PGM_ADDRESSING);
		}

		if (vcpu->run->s.regs.gprs[reg1] & PFMF_SK) {
			int rc = kvm_s390_skey_check_enable(vcpu);

			if (rc)
				return rc;
			down_read(&current->mm->mmap_sem);
			rc = cond_set_guest_storage_key(current->mm, vmaddr,
							key, NULL, nq, mr, mc);
			if (rc < 0) {
				rc = fixup_user_fault(current, current->mm, vmaddr,
						      FAULT_FLAG_WRITE, &unlocked);
				rc = !rc ? -EAGAIN : rc;
			}
			up_read(&current->mm->mmap_sem);
			if (rc == -EFAULT)
				return kvm_s390_inject_program_int(vcpu, PGM_ADDRESSING);
			if (rc == -EAGAIN)
				continue;
			if (rc < 0)
				return rc;
		}
		start += PAGE_SIZE;
	}
	if (vcpu->run->s.regs.gprs[reg1] & PFMF_FSC) {
		if (psw_bits(vcpu->arch.sie_block->gpsw).eaba == PSW_BITS_AMODE_64BIT) {
			vcpu->run->s.regs.gprs[reg2] = end;
		} else {
			vcpu->run->s.regs.gprs[reg2] &= ~0xffffffffUL;
			end = kvm_s390_logical_to_effective(vcpu, end);
			vcpu->run->s.regs.gprs[reg2] |= end;
		}
	}
	return 0;
}