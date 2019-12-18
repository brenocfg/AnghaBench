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
typedef  int ulong ;
struct kvmppc_book3s_shadow_vcpu {int slb_max; TYPE_1__* slb; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int esid; } ;

/* Variables and functions */
 int ESID_MASK ; 
 int SLB_ESID_V ; 
 int /*<<< orphan*/  kvmppc_mmu_flush_segments (struct kvm_vcpu*) ; 
 int mmu_slb_size ; 
 struct kvmppc_book3s_shadow_vcpu* svcpu_get (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  svcpu_put (struct kvmppc_book3s_shadow_vcpu*) ; 

__attribute__((used)) static int kvmppc_mmu_next_segment(struct kvm_vcpu *vcpu, ulong esid)
{
	struct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);
	int i;
	int max_slb_size = 64;
	int found_inval = -1;
	int r;

	/* Are we overwriting? */
	for (i = 0; i < svcpu->slb_max; i++) {
		if (!(svcpu->slb[i].esid & SLB_ESID_V))
			found_inval = i;
		else if ((svcpu->slb[i].esid & ESID_MASK) == esid) {
			r = i;
			goto out;
		}
	}

	/* Found a spare entry that was invalidated before */
	if (found_inval >= 0) {
		r = found_inval;
		goto out;
	}

	/* No spare invalid entry, so create one */

	if (mmu_slb_size < 64)
		max_slb_size = mmu_slb_size;

	/* Overflowing -> purge */
	if ((svcpu->slb_max) == max_slb_size)
		kvmppc_mmu_flush_segments(vcpu);

	r = svcpu->slb_max;
	svcpu->slb_max++;

out:
	svcpu_put(svcpu);
	return r;
}