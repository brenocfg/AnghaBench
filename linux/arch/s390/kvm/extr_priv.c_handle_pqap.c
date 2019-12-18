#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_14__ {TYPE_2__* sie_block; } ;
struct kvm_vcpu {TYPE_9__* run; TYPE_10__* kvm; TYPE_3__ arch; } ;
struct ap_queue_status {int response_code; } ;
typedef  int /*<<< orphan*/  status ;
struct TYPE_18__ {unsigned long* gprs; } ;
struct TYPE_19__ {TYPE_7__ regs; } ;
struct TYPE_20__ {TYPE_8__ s; } ;
struct TYPE_16__ {int crycbd; TYPE_4__* pqap_hook; } ;
struct TYPE_17__ {TYPE_5__ crypto; } ;
struct TYPE_15__ {int (* hook ) (struct kvm_vcpu*) ;int /*<<< orphan*/  owner; } ;
struct TYPE_12__ {int mask; } ;
struct TYPE_13__ {int eca; TYPE_1__ gpsw; } ;
struct TYPE_11__ {TYPE_6__ arch; } ;

/* Variables and functions */
 int ECA_APIE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PGM_PRIVILEGED_OP ; 
 int /*<<< orphan*/  PGM_SPECIFICATION ; 
 int PSW_MASK_PSTATE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ap_instructions_available () ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_set_psw_cc (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  memcpy (int*,struct ap_queue_status*,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  test_kvm_facility (TYPE_10__*,int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_pqap(struct kvm_vcpu *vcpu)
{
	struct ap_queue_status status = {};
	unsigned long reg0;
	int ret;
	uint8_t fc;

	/* Verify that the AP instruction are available */
	if (!ap_instructions_available())
		return -EOPNOTSUPP;
	/* Verify that the guest is allowed to use AP instructions */
	if (!(vcpu->arch.sie_block->eca & ECA_APIE))
		return -EOPNOTSUPP;
	/*
	 * The only possibly intercepted functions when AP instructions are
	 * available for the guest are AQIC and TAPQ with the t bit set
	 * since we do not set IC.3 (FIII) we currently will only intercept
	 * the AQIC function code.
	 */
	reg0 = vcpu->run->s.regs.gprs[0];
	fc = (reg0 >> 24) & 0xff;
	if (WARN_ON_ONCE(fc != 0x03))
		return -EOPNOTSUPP;

	/* PQAP instruction is allowed for guest kernel only */
	if (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		return kvm_s390_inject_program_int(vcpu, PGM_PRIVILEGED_OP);

	/* Common PQAP instruction specification exceptions */
	/* bits 41-47 must all be zeros */
	if (reg0 & 0x007f0000UL)
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);
	/* APFT not install and T bit set */
	if (!test_kvm_facility(vcpu->kvm, 15) && (reg0 & 0x00800000UL))
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);
	/* APXA not installed and APID greater 64 or APQI greater 16 */
	if (!(vcpu->kvm->arch.crypto.crycbd & 0x02) && (reg0 & 0x0000c0f0UL))
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

	/* AQIC function code specific exception */
	/* facility 65 not present for AQIC function code */
	if (!test_kvm_facility(vcpu->kvm, 65))
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

	/*
	 * Verify that the hook callback is registered, lock the owner
	 * and call the hook.
	 */
	if (vcpu->kvm->arch.crypto.pqap_hook) {
		if (!try_module_get(vcpu->kvm->arch.crypto.pqap_hook->owner))
			return -EOPNOTSUPP;
		ret = vcpu->kvm->arch.crypto.pqap_hook->hook(vcpu);
		module_put(vcpu->kvm->arch.crypto.pqap_hook->owner);
		if (!ret && vcpu->run->s.regs.gprs[1] & 0x00ff0000)
			kvm_s390_set_psw_cc(vcpu, 3);
		return ret;
	}
	/*
	 * A vfio_driver must register a hook.
	 * No hook means no driver to enable the SIE CRYCB and no queues.
	 * We send this response to the guest.
	 */
	status.response_code = 0x01;
	memcpy(&vcpu->run->s.regs.gprs[1], &status, sizeof(status));
	kvm_s390_set_psw_cc(vcpu, 3);
	return 0;
}