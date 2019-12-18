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
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct kvm_nested_guest {int /*<<< orphan*/  tlb_lock; int /*<<< orphan*/  shadow_lpid; } ;
typedef  int gva_t ;
typedef  scalar_t__ gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 long H_NOT_FOUND ; 
 long H_NO_MEM ; 
 long H_PARAMETER ; 
 long __kvmhv_copy_tofrom_guest_radix (int /*<<< orphan*/ ,int,int,void*,void*,unsigned long) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 long kvm_vcpu_read_guest (struct kvm_vcpu*,scalar_t__,void*,unsigned long) ; 
 long kvm_vcpu_write_guest (struct kvm_vcpu*,scalar_t__,void*,unsigned long) ; 
 struct kvm_nested_guest* kvmhv_get_nested (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kvmhv_put_nested (struct kvm_nested_guest*) ; 
 void* kvmppc_get_gpr (struct kvm_vcpu*,int) ; 
 void* kzalloc (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

long kvmhv_copy_tofrom_guest_nested(struct kvm_vcpu *vcpu)
{
	struct kvm_nested_guest *gp;
	int l1_lpid = kvmppc_get_gpr(vcpu, 4);
	int pid = kvmppc_get_gpr(vcpu, 5);
	gva_t eaddr = kvmppc_get_gpr(vcpu, 6);
	gpa_t gp_to = (gpa_t) kvmppc_get_gpr(vcpu, 7);
	gpa_t gp_from = (gpa_t) kvmppc_get_gpr(vcpu, 8);
	void *buf;
	unsigned long n = kvmppc_get_gpr(vcpu, 9);
	bool is_load = !!gp_to;
	long rc;

	if (gp_to && gp_from) /* One must be NULL to determine the direction */
		return H_PARAMETER;

	if (eaddr & (0xFFFUL << 52))
		return H_PARAMETER;

	buf = kzalloc(n, GFP_KERNEL);
	if (!buf)
		return H_NO_MEM;

	gp = kvmhv_get_nested(vcpu->kvm, l1_lpid, false);
	if (!gp) {
		rc = H_PARAMETER;
		goto out_free;
	}

	mutex_lock(&gp->tlb_lock);

	if (is_load) {
		/* Load from the nested guest into our buffer */
		rc = __kvmhv_copy_tofrom_guest_radix(gp->shadow_lpid, pid,
						     eaddr, buf, NULL, n);
		if (rc)
			goto not_found;

		/* Write what was loaded into our buffer back to the L1 guest */
		rc = kvm_vcpu_write_guest(vcpu, gp_to, buf, n);
		if (rc)
			goto not_found;
	} else {
		/* Load the data to be stored from the L1 guest into our buf */
		rc = kvm_vcpu_read_guest(vcpu, gp_from, buf, n);
		if (rc)
			goto not_found;

		/* Store from our buffer into the nested guest */
		rc = __kvmhv_copy_tofrom_guest_radix(gp->shadow_lpid, pid,
						     eaddr, NULL, buf, n);
		if (rc)
			goto not_found;
	}

out_unlock:
	mutex_unlock(&gp->tlb_lock);
	kvmhv_put_nested(gp);
out_free:
	kfree(buf);
	return rc;
not_found:
	rc = H_NOT_FOUND;
	goto out_unlock;
}