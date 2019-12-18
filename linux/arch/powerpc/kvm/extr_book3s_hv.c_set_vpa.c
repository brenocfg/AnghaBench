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
struct kvmppc_vpa {unsigned long next_gpa; unsigned long len; int update_pending; } ;
struct TYPE_2__ {int /*<<< orphan*/  vpa_update_lock; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int L1_CACHE_BYTES ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_vpa(struct kvm_vcpu *vcpu, struct kvmppc_vpa *v,
		   unsigned long addr, unsigned long len)
{
	/* check address is cacheline aligned */
	if (addr & (L1_CACHE_BYTES - 1))
		return -EINVAL;
	spin_lock(&vcpu->arch.vpa_update_lock);
	if (v->next_gpa != addr || v->len != len) {
		v->next_gpa = addr;
		v->len = addr ? len : 0;
		v->update_pending = 1;
	}
	spin_unlock(&vcpu->arch.vpa_update_lock);
	return 0;
}