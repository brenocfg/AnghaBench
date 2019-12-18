#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_vcpu_hv_synic {int /*<<< orphan*/  sint; } ;
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_hv_notify_acked_sint (struct kvm_vcpu*,int) ; 
 int synic_get_sint_vector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synic_read_sint (struct kvm_vcpu_hv_synic*,int) ; 
 int /*<<< orphan*/  trace_kvm_hv_synic_send_eoi (int /*<<< orphan*/ ,int) ; 
 struct kvm_vcpu_hv_synic* vcpu_to_synic (struct kvm_vcpu*) ; 

void kvm_hv_synic_send_eoi(struct kvm_vcpu *vcpu, int vector)
{
	struct kvm_vcpu_hv_synic *synic = vcpu_to_synic(vcpu);
	int i;

	trace_kvm_hv_synic_send_eoi(vcpu->vcpu_id, vector);

	for (i = 0; i < ARRAY_SIZE(synic->sint); i++)
		if (synic_get_sint_vector(synic_read_sint(synic, i)) == vector)
			kvm_hv_notify_acked_sint(vcpu, i);
}