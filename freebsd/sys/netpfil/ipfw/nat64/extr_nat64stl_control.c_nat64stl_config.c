#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockopt_data {int valsize; TYPE_1__* sopt; } ;
struct TYPE_9__ {int flags; } ;
struct nat64stl_cfg {TYPE_3__ base; } ;
struct namedobj_instance {int dummy; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_8__ {scalar_t__ set; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {TYPE_2__ ntlv; } ;
typedef  TYPE_4__ ipfw_obj_header ;
struct TYPE_11__ {int flags; } ;
typedef  TYPE_5__ ipfw_nat64stl_cfg ;
typedef  int /*<<< orphan*/  ip_fw3_opheader ;
struct TYPE_7__ {scalar_t__ sopt_dir; } ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_SRV (struct ip_fw_chain*) ; 
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ IPFW_MAX_SETS ; 
 int /*<<< orphan*/  IPFW_UH_RLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_RUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int NAT64STL_FLAGSMASK ; 
 scalar_t__ SOPT_GET ; 
 scalar_t__ ipfw_check_object_name_generic (int /*<<< orphan*/ ) ; 
 scalar_t__ ipfw_get_sopt_space (struct sockopt_data*,int) ; 
 int /*<<< orphan*/  nat64stl_export_config (struct ip_fw_chain*,struct nat64stl_cfg*,TYPE_5__*) ; 
 struct nat64stl_cfg* nat64stl_find (struct namedobj_instance*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
nat64stl_config(struct ip_fw_chain *ch, ip_fw3_opheader *op,
    struct sockopt_data *sd)
{
	ipfw_obj_header *oh;
	ipfw_nat64stl_cfg *uc;
	struct nat64stl_cfg *cfg;
	struct namedobj_instance *ni;

	if (sd->valsize != sizeof(*oh) + sizeof(*uc))
		return (EINVAL);

	oh = (ipfw_obj_header *)ipfw_get_sopt_space(sd,
	    sizeof(*oh) + sizeof(*uc));
	uc = (ipfw_nat64stl_cfg *)(oh + 1);

	if (ipfw_check_object_name_generic(oh->ntlv.name) != 0 ||
	    oh->ntlv.set >= IPFW_MAX_SETS)
		return (EINVAL);

	ni = CHAIN_TO_SRV(ch);
	if (sd->sopt->sopt_dir == SOPT_GET) {
		IPFW_UH_RLOCK(ch);
		cfg = nat64stl_find(ni, oh->ntlv.name, oh->ntlv.set);
		if (cfg == NULL) {
			IPFW_UH_RUNLOCK(ch);
			return (EEXIST);
		}
		nat64stl_export_config(ch, cfg, uc);
		IPFW_UH_RUNLOCK(ch);
		return (0);
	}

	IPFW_UH_WLOCK(ch);
	cfg = nat64stl_find(ni, oh->ntlv.name, oh->ntlv.set);
	if (cfg == NULL) {
		IPFW_UH_WUNLOCK(ch);
		return (EEXIST);
	}

	/*
	 * For now allow to change only following values:
	 *  flags.
	 */
	cfg->base.flags &= ~NAT64STL_FLAGSMASK;
	cfg->base.flags |= uc->flags & NAT64STL_FLAGSMASK;

	IPFW_UH_WUNLOCK(ch);
	return (0);
}