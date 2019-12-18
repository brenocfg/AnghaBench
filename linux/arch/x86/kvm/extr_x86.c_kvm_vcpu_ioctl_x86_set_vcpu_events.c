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
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int smm; scalar_t__ latched_init; scalar_t__ smm_inside_nmi; scalar_t__ pending; } ;
struct TYPE_20__ {int /*<<< orphan*/  masked; int /*<<< orphan*/  pending; int /*<<< orphan*/  injected; } ;
struct TYPE_19__ {int /*<<< orphan*/  shadow; int /*<<< orphan*/  soft; int /*<<< orphan*/  nr; int /*<<< orphan*/  injected; } ;
struct TYPE_16__ {int nr; int /*<<< orphan*/  error_code; int /*<<< orphan*/  has_error_code; scalar_t__ pending; scalar_t__ injected; } ;
struct kvm_vcpu_events {int flags; TYPE_8__ smi; int /*<<< orphan*/  sipi_vector; TYPE_7__ nmi; TYPE_6__ interrupt; int /*<<< orphan*/  exception_payload; scalar_t__ exception_has_payload; TYPE_3__ exception; } ;
struct TYPE_18__ {int /*<<< orphan*/  soft; int /*<<< orphan*/  nr; int /*<<< orphan*/  injected; } ;
struct TYPE_17__ {int nr; int /*<<< orphan*/  payload; scalar_t__ has_payload; int /*<<< orphan*/  error_code; int /*<<< orphan*/  has_error_code; scalar_t__ pending; scalar_t__ injected; } ;
struct TYPE_12__ {scalar_t__ mp_state; int hflags; TYPE_9__* apic; scalar_t__ smi_pending; int /*<<< orphan*/  nmi_pending; int /*<<< orphan*/  nmi_injected; TYPE_5__ interrupt; TYPE_4__ exception; } ;
struct kvm_vcpu {TYPE_10__ arch; TYPE_2__* kvm; } ;
struct TYPE_22__ {int /*<<< orphan*/  pending_events; int /*<<< orphan*/  sipi_vector; } ;
struct TYPE_14__ {int /*<<< orphan*/  exception_payload_enabled; } ;
struct TYPE_15__ {TYPE_1__ arch; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* set_nmi_mask ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_interrupt_shadow ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int HF_SMM_INSIDE_NMI_MASK ; 
 int HF_SMM_MASK ; 
 int /*<<< orphan*/  KVM_APIC_INIT ; 
 scalar_t__ KVM_MP_STATE_INIT_RECEIVED ; 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int KVM_VCPUEVENT_VALID_NMI_PENDING ; 
 int KVM_VCPUEVENT_VALID_PAYLOAD ; 
 int KVM_VCPUEVENT_VALID_SHADOW ; 
 int KVM_VCPUEVENT_VALID_SIPI_VECTOR ; 
 int KVM_VCPUEVENT_VALID_SMM ; 
 int NMI_VECTOR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_smm_changed (struct kvm_vcpu*) ; 
 TYPE_11__* kvm_x86_ops ; 
 scalar_t__ lapic_in_kernel (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  process_nmi (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_vcpu_ioctl_x86_set_vcpu_events(struct kvm_vcpu *vcpu,
					      struct kvm_vcpu_events *events)
{
	if (events->flags & ~(KVM_VCPUEVENT_VALID_NMI_PENDING
			      | KVM_VCPUEVENT_VALID_SIPI_VECTOR
			      | KVM_VCPUEVENT_VALID_SHADOW
			      | KVM_VCPUEVENT_VALID_SMM
			      | KVM_VCPUEVENT_VALID_PAYLOAD))
		return -EINVAL;

	if (events->flags & KVM_VCPUEVENT_VALID_PAYLOAD) {
		if (!vcpu->kvm->arch.exception_payload_enabled)
			return -EINVAL;
		if (events->exception.pending)
			events->exception.injected = 0;
		else
			events->exception_has_payload = 0;
	} else {
		events->exception.pending = 0;
		events->exception_has_payload = 0;
	}

	if ((events->exception.injected || events->exception.pending) &&
	    (events->exception.nr > 31 || events->exception.nr == NMI_VECTOR))
		return -EINVAL;

	/* INITs are latched while in SMM */
	if (events->flags & KVM_VCPUEVENT_VALID_SMM &&
	    (events->smi.smm || events->smi.pending) &&
	    vcpu->arch.mp_state == KVM_MP_STATE_INIT_RECEIVED)
		return -EINVAL;

	process_nmi(vcpu);
	vcpu->arch.exception.injected = events->exception.injected;
	vcpu->arch.exception.pending = events->exception.pending;
	vcpu->arch.exception.nr = events->exception.nr;
	vcpu->arch.exception.has_error_code = events->exception.has_error_code;
	vcpu->arch.exception.error_code = events->exception.error_code;
	vcpu->arch.exception.has_payload = events->exception_has_payload;
	vcpu->arch.exception.payload = events->exception_payload;

	vcpu->arch.interrupt.injected = events->interrupt.injected;
	vcpu->arch.interrupt.nr = events->interrupt.nr;
	vcpu->arch.interrupt.soft = events->interrupt.soft;
	if (events->flags & KVM_VCPUEVENT_VALID_SHADOW)
		kvm_x86_ops->set_interrupt_shadow(vcpu,
						  events->interrupt.shadow);

	vcpu->arch.nmi_injected = events->nmi.injected;
	if (events->flags & KVM_VCPUEVENT_VALID_NMI_PENDING)
		vcpu->arch.nmi_pending = events->nmi.pending;
	kvm_x86_ops->set_nmi_mask(vcpu, events->nmi.masked);

	if (events->flags & KVM_VCPUEVENT_VALID_SIPI_VECTOR &&
	    lapic_in_kernel(vcpu))
		vcpu->arch.apic->sipi_vector = events->sipi_vector;

	if (events->flags & KVM_VCPUEVENT_VALID_SMM) {
		if (!!(vcpu->arch.hflags & HF_SMM_MASK) != events->smi.smm) {
			if (events->smi.smm)
				vcpu->arch.hflags |= HF_SMM_MASK;
			else
				vcpu->arch.hflags &= ~HF_SMM_MASK;
			kvm_smm_changed(vcpu);
		}

		vcpu->arch.smi_pending = events->smi.pending;

		if (events->smi.smm) {
			if (events->smi.smm_inside_nmi)
				vcpu->arch.hflags |= HF_SMM_INSIDE_NMI_MASK;
			else
				vcpu->arch.hflags &= ~HF_SMM_INSIDE_NMI_MASK;
			if (lapic_in_kernel(vcpu)) {
				if (events->smi.latched_init)
					set_bit(KVM_APIC_INIT, &vcpu->arch.apic->pending_events);
				else
					clear_bit(KVM_APIC_INIT, &vcpu->arch.apic->pending_events);
			}
		}
	}

	kvm_make_request(KVM_REQ_EVENT, vcpu);

	return 0;
}