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
typedef  int u64 ;
struct TYPE_16__ {TYPE_2__* sie_block; } ;
struct TYPE_14__ {int /*<<< orphan*/  instruction_sske; } ;
struct kvm_vcpu {TYPE_6__* run; TYPE_3__ arch; int /*<<< orphan*/  kvm; TYPE_1__ stat; } ;
struct TYPE_22__ {TYPE_10__* mm; } ;
struct TYPE_21__ {int mask; } ;
struct TYPE_20__ {scalar_t__ eaba; } ;
struct TYPE_17__ {int* gprs; } ;
struct TYPE_18__ {TYPE_4__ regs; } ;
struct TYPE_19__ {TYPE_5__ s; } ;
struct TYPE_15__ {int ipb; TYPE_8__ gpsw; } ;
struct TYPE_13__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EFAULT ; 
 int /*<<< orphan*/  FAULT_FLAG_WRITE ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  PGM_ADDRESSING ; 
 int /*<<< orphan*/  PGM_PRIVILEGED_OP ; 
 scalar_t__ PSW_BITS_AMODE_64BIT ; 
 int PSW_MASK_PSTATE ; 
 unsigned char SSKE_MB ; 
 unsigned char SSKE_MC ; 
 unsigned char SSKE_MR ; 
 unsigned char SSKE_NQ ; 
 unsigned long _SEGMENT_SIZE ; 
 int cond_set_guest_storage_key (TYPE_10__*,unsigned long,unsigned char,unsigned char*,unsigned char,unsigned char,unsigned char) ; 
 TYPE_9__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int fixup_user_fault (TYPE_9__*,TYPE_10__*,unsigned long,int /*<<< orphan*/ ,int*) ; 
 unsigned long gfn_to_hva (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpa_to_gfn (unsigned long) ; 
 scalar_t__ kvm_is_error_hva (unsigned long) ; 
 int /*<<< orphan*/  kvm_s390_get_regs_rre (struct kvm_vcpu*,int*,int*) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 unsigned long kvm_s390_logical_to_effective (struct kvm_vcpu*,unsigned long) ; 
 unsigned long kvm_s390_real_to_abs (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  kvm_s390_set_psw_cc (struct kvm_vcpu*,int) ; 
 TYPE_7__ psw_bits (TYPE_8__) ; 
 int /*<<< orphan*/  test_kvm_facility (int /*<<< orphan*/ ,int) ; 
 int try_handle_skey (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_sske(struct kvm_vcpu *vcpu)
{
	unsigned char m3 = vcpu->arch.sie_block->ipb >> 28;
	unsigned long start, end;
	unsigned char key, oldkey;
	int reg1, reg2;
	bool unlocked;
	int rc;

	vcpu->stat.instruction_sske++;

	if (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		return kvm_s390_inject_program_int(vcpu, PGM_PRIVILEGED_OP);

	rc = try_handle_skey(vcpu);
	if (rc)
		return rc != -EAGAIN ? rc : 0;

	if (!test_kvm_facility(vcpu->kvm, 8))
		m3 &= ~SSKE_MB;
	if (!test_kvm_facility(vcpu->kvm, 10))
		m3 &= ~(SSKE_MC | SSKE_MR);
	if (!test_kvm_facility(vcpu->kvm, 14))
		m3 &= ~SSKE_NQ;

	kvm_s390_get_regs_rre(vcpu, &reg1, &reg2);

	key = vcpu->run->s.regs.gprs[reg1] & 0xfe;
	start = vcpu->run->s.regs.gprs[reg2] & PAGE_MASK;
	start = kvm_s390_logical_to_effective(vcpu, start);
	if (m3 & SSKE_MB) {
		/* start already designates an absolute address */
		end = (start + _SEGMENT_SIZE) & ~(_SEGMENT_SIZE - 1);
	} else {
		start = kvm_s390_real_to_abs(vcpu, start);
		end = start + PAGE_SIZE;
	}

	while (start != end) {
		unsigned long vmaddr = gfn_to_hva(vcpu->kvm, gpa_to_gfn(start));
		unlocked = false;

		if (kvm_is_error_hva(vmaddr))
			return kvm_s390_inject_program_int(vcpu, PGM_ADDRESSING);

		down_read(&current->mm->mmap_sem);
		rc = cond_set_guest_storage_key(current->mm, vmaddr, key, &oldkey,
						m3 & SSKE_NQ, m3 & SSKE_MR,
						m3 & SSKE_MC);

		if (rc < 0) {
			rc = fixup_user_fault(current, current->mm, vmaddr,
					      FAULT_FLAG_WRITE, &unlocked);
			rc = !rc ? -EAGAIN : rc;
		}
		up_read(&current->mm->mmap_sem);
		if (rc == -EFAULT)
			return kvm_s390_inject_program_int(vcpu, PGM_ADDRESSING);
		if (rc < 0)
			return rc;
		start += PAGE_SIZE;
	}

	if (m3 & (SSKE_MC | SSKE_MR)) {
		if (m3 & SSKE_MB) {
			/* skey in reg1 is unpredictable */
			kvm_s390_set_psw_cc(vcpu, 3);
		} else {
			kvm_s390_set_psw_cc(vcpu, rc);
			vcpu->run->s.regs.gprs[reg1] &= ~0xff00UL;
			vcpu->run->s.regs.gprs[reg1] |= (u64) oldkey << 8;
		}
	}
	if (m3 & SSKE_MB) {
		if (psw_bits(vcpu->arch.sie_block->gpsw).eaba == PSW_BITS_AMODE_64BIT)
			vcpu->run->s.regs.gprs[reg2] &= ~PAGE_MASK;
		else
			vcpu->run->s.regs.gprs[reg2] &= ~0xfffff000UL;
		end = kvm_s390_logical_to_effective(vcpu, end);
		vcpu->run->s.regs.gprs[reg2] |= end;
	}
	return 0;
}