#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct tp_params {unsigned long long vlan_shift; unsigned long long port_shift; unsigned long long protocol_shift; unsigned long long tos_shift; unsigned long long vnic_shift; int ingress_config; unsigned long long macmatch_shift; unsigned long long ethertype_shift; unsigned long long matchtype_shift; unsigned long long frag_shift; unsigned long long fcoe_shift; unsigned long long hash_filter_mask; } ;
struct TYPE_6__ {unsigned long long vlan; unsigned long long vnic; scalar_t__ fcoe; scalar_t__ frag; scalar_t__ matchtype; scalar_t__ ethtype; scalar_t__ macidx; scalar_t__ tos; scalar_t__ proto; scalar_t__ iport; } ;
struct TYPE_5__ {scalar_t__ fcoe; scalar_t__ frag; scalar_t__ matchtype; scalar_t__ ethtype; scalar_t__ macidx; int /*<<< orphan*/  ovlan_vld; int /*<<< orphan*/  pfvf_vld; scalar_t__ vnic; scalar_t__ tos; scalar_t__ proto; scalar_t__ iport; scalar_t__ vlan; } ;
struct t4_filter_specification {TYPE_3__ val; TYPE_2__ mask; } ;
struct TYPE_4__ {struct tp_params tp; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long long F_FT_VLAN_VLD ; 
 int F_VNIC ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 unsigned long long M_FT_ETHERTYPE ; 
 unsigned long long M_FT_FCOE ; 
 unsigned long long M_FT_FRAGMENTATION ; 
 unsigned long long M_FT_MACMATCH ; 
 unsigned long long M_FT_MPSHITTYPE ; 
 unsigned long long M_FT_PORT ; 
 unsigned long long M_FT_PROTOCOL ; 
 unsigned long long M_FT_TOS ; 
 unsigned long long M_FT_VLAN ; 
 unsigned long long M_FT_VNIC_ID ; 

__attribute__((used)) static int
hashfilter_ntuple(struct adapter *sc, const struct t4_filter_specification *fs,
    uint64_t *ftuple)
{
	struct tp_params *tp = &sc->params.tp;
	uint64_t fmask;

	*ftuple = fmask = 0;

	/*
	 * Initialize each of the fields which we care about which are present
	 * in the Compressed Filter Tuple.
	 */
	if (tp->vlan_shift >= 0 && fs->mask.vlan) {
		*ftuple |= (F_FT_VLAN_VLD | fs->val.vlan) << tp->vlan_shift;
		fmask |= M_FT_VLAN << tp->vlan_shift;
	}

	if (tp->port_shift >= 0 && fs->mask.iport) {
		*ftuple |= (uint64_t)fs->val.iport << tp->port_shift;
		fmask |= M_FT_PORT << tp->port_shift;
	}

	if (tp->protocol_shift >= 0 && fs->mask.proto) {
		*ftuple |= (uint64_t)fs->val.proto << tp->protocol_shift;
		fmask |= M_FT_PROTOCOL << tp->protocol_shift;
	}

	if (tp->tos_shift >= 0 && fs->mask.tos) {
		*ftuple |= (uint64_t)(fs->val.tos) << tp->tos_shift;
		fmask |= M_FT_TOS << tp->tos_shift;
	}

	if (tp->vnic_shift >= 0 && fs->mask.vnic) {
		/* F_VNIC in ingress config was already validated. */
		if (tp->ingress_config & F_VNIC)
			MPASS(fs->mask.pfvf_vld);
		else
			MPASS(fs->mask.ovlan_vld);

		*ftuple |= ((1ULL << 16) | fs->val.vnic) << tp->vnic_shift;
		fmask |= M_FT_VNIC_ID << tp->vnic_shift;
	}

	if (tp->macmatch_shift >= 0 && fs->mask.macidx) {
		*ftuple |= (uint64_t)(fs->val.macidx) << tp->macmatch_shift;
		fmask |= M_FT_MACMATCH << tp->macmatch_shift;
	}

	if (tp->ethertype_shift >= 0 && fs->mask.ethtype) {
		*ftuple |= (uint64_t)(fs->val.ethtype) << tp->ethertype_shift;
		fmask |= M_FT_ETHERTYPE << tp->ethertype_shift;
	}

	if (tp->matchtype_shift >= 0 && fs->mask.matchtype) {
		*ftuple |= (uint64_t)(fs->val.matchtype) << tp->matchtype_shift;
		fmask |= M_FT_MPSHITTYPE << tp->matchtype_shift;
	}

	if (tp->frag_shift >= 0 && fs->mask.frag) {
		*ftuple |= (uint64_t)(fs->val.frag) << tp->frag_shift;
		fmask |= M_FT_FRAGMENTATION << tp->frag_shift;
	}

	if (tp->fcoe_shift >= 0 && fs->mask.fcoe) {
		*ftuple |= (uint64_t)(fs->val.fcoe) << tp->fcoe_shift;
		fmask |= M_FT_FCOE << tp->fcoe_shift;
	}

	/* A hashfilter must conform to the filterMask. */
	if (fmask != tp->hash_filter_mask)
		return (EINVAL);

	return (0);
}