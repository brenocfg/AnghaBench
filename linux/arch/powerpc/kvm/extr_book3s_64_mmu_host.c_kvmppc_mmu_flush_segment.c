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
 int SLB_ESID_V ; 
 struct kvmppc_book3s_shadow_vcpu* svcpu_get (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  svcpu_put (struct kvmppc_book3s_shadow_vcpu*) ; 

void kvmppc_mmu_flush_segment(struct kvm_vcpu *vcpu, ulong ea, ulong seg_size)
{
	struct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);
	ulong seg_mask = -seg_size;
	int i;

	for (i = 0; i < svcpu->slb_max; i++) {
		if ((svcpu->slb[i].esid & SLB_ESID_V) &&
		    (svcpu->slb[i].esid & seg_mask) == ea) {
			/* Invalidate this entry */
			svcpu->slb[i].esid = 0;
		}
	}

	svcpu_put(svcpu);
}