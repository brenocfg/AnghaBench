#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct TYPE_10__ {int /*<<< orphan*/  instruction_lpsw; } ;
struct TYPE_9__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_3__ stat; TYPE_2__ arch; } ;
struct TYPE_11__ {int mask; int addr; } ;
typedef  TYPE_4__ psw_t ;
struct TYPE_12__ {int mask; int addr; } ;
typedef  TYPE_5__ psw_compat_t ;
typedef  int /*<<< orphan*/  new_psw ;
struct TYPE_8__ {TYPE_4__ gpsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PGM_PRIVILEGED_OP ; 
 int /*<<< orphan*/  PGM_SPECIFICATION ; 
 int PSW32_ADDR_AMODE ; 
 int PSW32_MASK_BASE ; 
 int PSW_MASK_PSTATE ; 
 int /*<<< orphan*/  is_valid_psw (TYPE_4__*) ; 
 int kvm_s390_get_base_disp_s (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 int kvm_s390_inject_prog_cond (struct kvm_vcpu*,int) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int read_guest (struct kvm_vcpu*,int,int /*<<< orphan*/ ,TYPE_5__*,int) ; 

int kvm_s390_handle_lpsw(struct kvm_vcpu *vcpu)
{
	psw_t *gpsw = &vcpu->arch.sie_block->gpsw;
	psw_compat_t new_psw;
	u64 addr;
	int rc;
	u8 ar;

	vcpu->stat.instruction_lpsw++;

	if (gpsw->mask & PSW_MASK_PSTATE)
		return kvm_s390_inject_program_int(vcpu, PGM_PRIVILEGED_OP);

	addr = kvm_s390_get_base_disp_s(vcpu, &ar);
	if (addr & 7)
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

	rc = read_guest(vcpu, addr, ar, &new_psw, sizeof(new_psw));
	if (rc)
		return kvm_s390_inject_prog_cond(vcpu, rc);
	if (!(new_psw.mask & PSW32_MASK_BASE))
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);
	gpsw->mask = (new_psw.mask & ~PSW32_MASK_BASE) << 32;
	gpsw->mask |= new_psw.addr & PSW32_ADDR_AMODE;
	gpsw->addr = new_psw.addr & ~PSW32_ADDR_AMODE;
	if (!is_valid_psw(gpsw))
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);
	return 0;
}