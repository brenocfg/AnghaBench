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
typedef  int u64 ;
struct sthyi_sctns {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  instruction_sthyi; } ;
struct kvm_vcpu {TYPE_4__* run; TYPE_1__ stat; int /*<<< orphan*/  kvm; } ;
struct TYPE_6__ {int* gprs; } ;
struct TYPE_7__ {TYPE_2__ regs; } ;
struct TYPE_8__ {TYPE_3__ s; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PGM_OPERATION ; 
 int /*<<< orphan*/  PGM_SPECIFICATION ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,int,int) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_get_regs_rre (struct kvm_vcpu*,int*,int*) ; 
 int kvm_s390_inject_prog_cond (struct kvm_vcpu*,int) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_set_psw_cc (struct kvm_vcpu*,int) ; 
 int sthyi_fill (struct sthyi_sctns*,int*) ; 
 int /*<<< orphan*/  test_kvm_facility (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_kvm_s390_handle_sthyi (struct kvm_vcpu*,int,int) ; 
 int write_guest (struct kvm_vcpu*,int,int,struct sthyi_sctns*,int /*<<< orphan*/ ) ; 

int handle_sthyi(struct kvm_vcpu *vcpu)
{
	int reg1, reg2, r = 0;
	u64 code, addr, cc = 0, rc = 0;
	struct sthyi_sctns *sctns = NULL;

	if (!test_kvm_facility(vcpu->kvm, 74))
		return kvm_s390_inject_program_int(vcpu, PGM_OPERATION);

	kvm_s390_get_regs_rre(vcpu, &reg1, &reg2);
	code = vcpu->run->s.regs.gprs[reg1];
	addr = vcpu->run->s.regs.gprs[reg2];

	vcpu->stat.instruction_sthyi++;
	VCPU_EVENT(vcpu, 3, "STHYI: fc: %llu addr: 0x%016llx", code, addr);
	trace_kvm_s390_handle_sthyi(vcpu, code, addr);

	if (reg1 == reg2 || reg1 & 1 || reg2 & 1)
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

	if (code & 0xffff) {
		cc = 3;
		rc = 4;
		goto out;
	}

	if (addr & ~PAGE_MASK)
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

	sctns = (void *)get_zeroed_page(GFP_KERNEL);
	if (!sctns)
		return -ENOMEM;

	cc = sthyi_fill(sctns, &rc);

out:
	if (!cc) {
		r = write_guest(vcpu, addr, reg2, sctns, PAGE_SIZE);
		if (r) {
			free_page((unsigned long)sctns);
			return kvm_s390_inject_prog_cond(vcpu, r);
		}
	}

	free_page((unsigned long)sctns);
	vcpu->run->s.regs.gprs[reg2 + 1] = rc;
	kvm_s390_set_psw_cc(vcpu, cc);
	return r;
}