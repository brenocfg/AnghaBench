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
typedef  int uint32_t ;
struct tp_params {int ingress_config; int vlan_pri_map; } ;
struct TYPE_6__ {scalar_t__ fcoe; scalar_t__ iport; scalar_t__ pfvf_vld; scalar_t__ ovlan_vld; scalar_t__ vlan_vld; scalar_t__ tos; scalar_t__ proto; scalar_t__ ethtype; scalar_t__ macidx; scalar_t__ matchtype; scalar_t__ frag; } ;
struct TYPE_5__ {scalar_t__ fcoe; scalar_t__ iport; scalar_t__ pfvf_vld; scalar_t__ ovlan_vld; scalar_t__ vlan_vld; scalar_t__ tos; scalar_t__ proto; scalar_t__ ethtype; scalar_t__ macidx; scalar_t__ matchtype; scalar_t__ frag; } ;
struct t4_filter_specification {TYPE_3__ mask; TYPE_2__ val; } ;
struct TYPE_4__ {struct tp_params tp; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int F_ETHERTYPE ; 
 int F_FCOE ; 
 int F_FRAGMENTATION ; 
 int F_MACMATCH ; 
 int F_MPSHITTYPE ; 
 int F_PORT ; 
 int F_PROTOCOL ; 
 int F_TOS ; 
 int F_VLAN ; 
 int F_VNIC ; 
 int F_VNIC_ID ; 

__attribute__((used)) static int
check_fspec_against_fconf_iconf(struct adapter *sc,
    struct t4_filter_specification *fs)
{
	struct tp_params *tpp = &sc->params.tp;
	uint32_t fconf = 0;

	if (fs->val.frag || fs->mask.frag)
		fconf |= F_FRAGMENTATION;

	if (fs->val.matchtype || fs->mask.matchtype)
		fconf |= F_MPSHITTYPE;

	if (fs->val.macidx || fs->mask.macidx)
		fconf |= F_MACMATCH;

	if (fs->val.ethtype || fs->mask.ethtype)
		fconf |= F_ETHERTYPE;

	if (fs->val.proto || fs->mask.proto)
		fconf |= F_PROTOCOL;

	if (fs->val.tos || fs->mask.tos)
		fconf |= F_TOS;

	if (fs->val.vlan_vld || fs->mask.vlan_vld)
		fconf |= F_VLAN;

	if (fs->val.ovlan_vld || fs->mask.ovlan_vld) {
		fconf |= F_VNIC_ID;
		if (tpp->ingress_config & F_VNIC)
			return (EINVAL);
	}

	if (fs->val.pfvf_vld || fs->mask.pfvf_vld) {
		fconf |= F_VNIC_ID;
		if ((tpp->ingress_config & F_VNIC) == 0)
			return (EINVAL);
	}

	if (fs->val.iport || fs->mask.iport)
		fconf |= F_PORT;

	if (fs->val.fcoe || fs->mask.fcoe)
		fconf |= F_FCOE;

	if ((tpp->vlan_pri_map | fconf) != tpp->vlan_pri_map)
		return (E2BIG);

	return (0);
}