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
typedef  scalar_t__ u64 ;
typedef  size_t u16 ;
struct kvmppc_sid_map {scalar_t__ guest_vsid; int /*<<< orphan*/  host_vsid; scalar_t__ valid; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {struct kvmppc_sid_map* sid_map; } ;

/* Variables and functions */
 int MSR_PR ; 
 size_t SID_MAP_MASK ; 
 scalar_t__ VSID_PR ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 size_t kvmppc_sid_hash (struct kvm_vcpu*,scalar_t__) ; 
 TYPE_1__* to_book3s (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_book3s_slb_fail (size_t,scalar_t__) ; 
 int /*<<< orphan*/  trace_kvm_book3s_slb_found (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kvmppc_sid_map *find_sid_vsid(struct kvm_vcpu *vcpu, u64 gvsid)
{
	struct kvmppc_sid_map *map;
	u16 sid_map_mask;

	if (kvmppc_get_msr(vcpu) & MSR_PR)
		gvsid |= VSID_PR;

	sid_map_mask = kvmppc_sid_hash(vcpu, gvsid);
	map = &to_book3s(vcpu)->sid_map[sid_map_mask];
	if (map->valid && (map->guest_vsid == gvsid)) {
		trace_kvm_book3s_slb_found(gvsid, map->host_vsid);
		return map;
	}

	map = &to_book3s(vcpu)->sid_map[SID_MAP_MASK - sid_map_mask];
	if (map->valid && (map->guest_vsid == gvsid)) {
		trace_kvm_book3s_slb_found(gvsid, map->host_vsid);
		return map;
	}

	trace_kvm_book3s_slb_fail(sid_map_mask, gvsid);
	return NULL;
}