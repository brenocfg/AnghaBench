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
typedef  int ulong ;
typedef  int u64 ;
struct kvmppc_sid_map {int guest_esid; int host_vsid; } ;
struct kvmppc_book3s_shadow_vcpu {TYPE_3__* slb; } ;
struct TYPE_5__ {scalar_t__ (* esid_to_vsid ) (struct kvm_vcpu*,int,int*) ;} ;
struct TYPE_6__ {TYPE_1__ mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_8__ {int sllp; } ;
struct TYPE_7__ {int esid; int vsid; } ;

/* Variables and functions */
 int ENOENT ; 
 int ESID_MASK ; 
 size_t MMU_PAGE_64K ; 
 int SID_SHIFT ; 
 int SLB_ESID_V ; 
 int SLB_VSID_KP ; 
 int SLB_VSID_USER ; 
 int VSID_64K ; 
 struct kvmppc_sid_map* create_sid_map (struct kvm_vcpu*,int) ; 
 struct kvmppc_sid_map* find_sid_vsid (struct kvm_vcpu*,int) ; 
 int kvmppc_mmu_next_segment (struct kvm_vcpu*,int) ; 
 TYPE_4__* mmu_psize_defs ; 
 scalar_t__ stub1 (struct kvm_vcpu*,int,int*) ; 
 struct kvmppc_book3s_shadow_vcpu* svcpu_get (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  svcpu_put (struct kvmppc_book3s_shadow_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_book3s_slbmte (int,int) ; 

int kvmppc_mmu_map_segment(struct kvm_vcpu *vcpu, ulong eaddr)
{
	struct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);
	u64 esid = eaddr >> SID_SHIFT;
	u64 slb_esid = (eaddr & ESID_MASK) | SLB_ESID_V;
	u64 slb_vsid = SLB_VSID_USER;
	u64 gvsid;
	int slb_index;
	struct kvmppc_sid_map *map;
	int r = 0;

	slb_index = kvmppc_mmu_next_segment(vcpu, eaddr & ESID_MASK);

	if (vcpu->arch.mmu.esid_to_vsid(vcpu, esid, &gvsid)) {
		/* Invalidate an entry */
		svcpu->slb[slb_index].esid = 0;
		r = -ENOENT;
		goto out;
	}

	map = find_sid_vsid(vcpu, gvsid);
	if (!map)
		map = create_sid_map(vcpu, gvsid);

	map->guest_esid = esid;

	slb_vsid |= (map->host_vsid << 12);
	slb_vsid &= ~SLB_VSID_KP;
	slb_esid |= slb_index;

#ifdef CONFIG_PPC_64K_PAGES
	/* Set host segment base page size to 64K if possible */
	if (gvsid & VSID_64K)
		slb_vsid |= mmu_psize_defs[MMU_PAGE_64K].sllp;
#endif

	svcpu->slb[slb_index].esid = slb_esid;
	svcpu->slb[slb_index].vsid = slb_vsid;

	trace_kvm_book3s_slbmte(slb_vsid, slb_esid);

out:
	svcpu_put(svcpu);
	return r;
}