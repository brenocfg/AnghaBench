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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  tpi_data ;
struct TYPE_7__ {TYPE_2__* sie_block; } ;
struct TYPE_5__ {int /*<<< orphan*/  instruction_tpi; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_3__ arch; TYPE_1__ stat; } ;
struct TYPE_8__ {int subchannel_id; int subchannel_nr; int io_int_parm; int io_int_word; } ;
struct kvm_s390_interrupt_info {TYPE_4__ io; } ;
struct TYPE_6__ {int /*<<< orphan*/ * gcr; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  PGM_SPECIFICATION ; 
 int /*<<< orphan*/  __LC_SUBCHANNEL_ID ; 
 int /*<<< orphan*/  kfree (struct kvm_s390_interrupt_info*) ; 
 int kvm_s390_get_base_disp_s (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 struct kvm_s390_interrupt_info* kvm_s390_get_io_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kvm_s390_inject_prog_cond (struct kvm_vcpu*,int) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_s390_reinject_io_int (int /*<<< orphan*/ ,struct kvm_s390_interrupt_info*) ; 
 int /*<<< orphan*/  kvm_s390_set_psw_cc (struct kvm_vcpu*,int) ; 
 int write_guest (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int**,unsigned long) ; 
 scalar_t__ write_guest_lc (struct kvm_vcpu*,int /*<<< orphan*/ ,int**,unsigned long) ; 

__attribute__((used)) static int handle_tpi(struct kvm_vcpu *vcpu)
{
	struct kvm_s390_interrupt_info *inti;
	unsigned long len;
	u32 tpi_data[3];
	int rc;
	u64 addr;
	u8 ar;

	vcpu->stat.instruction_tpi++;

	addr = kvm_s390_get_base_disp_s(vcpu, &ar);
	if (addr & 3)
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

	inti = kvm_s390_get_io_int(vcpu->kvm, vcpu->arch.sie_block->gcr[6], 0);
	if (!inti) {
		kvm_s390_set_psw_cc(vcpu, 0);
		return 0;
	}

	tpi_data[0] = inti->io.subchannel_id << 16 | inti->io.subchannel_nr;
	tpi_data[1] = inti->io.io_int_parm;
	tpi_data[2] = inti->io.io_int_word;
	if (addr) {
		/*
		 * Store the two-word I/O interruption code into the
		 * provided area.
		 */
		len = sizeof(tpi_data) - 4;
		rc = write_guest(vcpu, addr, ar, &tpi_data, len);
		if (rc) {
			rc = kvm_s390_inject_prog_cond(vcpu, rc);
			goto reinject_interrupt;
		}
	} else {
		/*
		 * Store the three-word I/O interruption code into
		 * the appropriate lowcore area.
		 */
		len = sizeof(tpi_data);
		if (write_guest_lc(vcpu, __LC_SUBCHANNEL_ID, &tpi_data, len)) {
			/* failed writes to the low core are not recoverable */
			rc = -EFAULT;
			goto reinject_interrupt;
		}
	}

	/* irq was successfully handed to the guest */
	kfree(inti);
	kvm_s390_set_psw_cc(vcpu, 1);
	return 0;
reinject_interrupt:
	/*
	 * If we encounter a problem storing the interruption code, the
	 * instruction is suppressed from the guest's view: reinject the
	 * interrupt.
	 */
	if (kvm_s390_reinject_io_int(vcpu->kvm, inti)) {
		kfree(inti);
		rc = -EFAULT;
	}
	/* don't set the cc, a pgm irq was injected or we drop to user space */
	return rc ? -EFAULT : 0;
}