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
typedef  int uint32_t ;
struct sockopt_data {int valsize; TYPE_1__* sopt; } ;
struct TYPE_9__ {scalar_t__ plat_plen; scalar_t__ clat_plen; int flags; int /*<<< orphan*/  clat_prefix; int /*<<< orphan*/  plat_prefix; } ;
struct nat64clat_cfg {TYPE_3__ base; } ;
struct namedobj_instance {int dummy; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_8__ {scalar_t__ set; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {TYPE_2__ ntlv; } ;
typedef  TYPE_4__ ipfw_obj_header ;
struct TYPE_11__ {scalar_t__ plat_plen; scalar_t__ clat_plen; int flags; int /*<<< orphan*/  clat_prefix; int /*<<< orphan*/  plat_prefix; } ;
typedef  TYPE_5__ ipfw_nat64clat_cfg ;
typedef  int /*<<< orphan*/  ip_fw3_opheader ;
struct TYPE_7__ {scalar_t__ sopt_dir; } ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_SRV (struct ip_fw_chain*) ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  IN6_ARE_ADDR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IPFW_MAX_SETS ; 
 int /*<<< orphan*/  IPFW_UH_RLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_RUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WUNLOCK (struct ip_fw_chain*) ; 
 int NAT64CLAT_FLAGSMASK ; 
 int NAT64_CLATPFX ; 
 int NAT64_PLATPFX ; 
 scalar_t__ SOPT_GET ; 
 scalar_t__ ipfw_check_object_name_generic (int /*<<< orphan*/ ) ; 
 scalar_t__ ipfw_get_sopt_space (struct sockopt_data*,int) ; 
 scalar_t__ nat64_check_prefix6 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  nat64clat_export_config (struct ip_fw_chain*,struct nat64clat_cfg*,TYPE_5__*) ; 
 struct nat64clat_cfg* nat64clat_find (struct namedobj_instance*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
nat64clat_config(struct ip_fw_chain *ch, ip_fw3_opheader *op,
    struct sockopt_data *sd)
{
	ipfw_obj_header *oh;
	ipfw_nat64clat_cfg *uc;
	struct nat64clat_cfg *cfg;
	struct namedobj_instance *ni;
	uint32_t flags;

	if (sd->valsize != sizeof(*oh) + sizeof(*uc))
		return (EINVAL);

	oh = (ipfw_obj_header *)ipfw_get_sopt_space(sd,
	    sizeof(*oh) + sizeof(*uc));
	uc = (ipfw_nat64clat_cfg *)(oh + 1);

	if (ipfw_check_object_name_generic(oh->ntlv.name) != 0 ||
	    oh->ntlv.set >= IPFW_MAX_SETS)
		return (EINVAL);

	ni = CHAIN_TO_SRV(ch);
	if (sd->sopt->sopt_dir == SOPT_GET) {
		IPFW_UH_RLOCK(ch);
		cfg = nat64clat_find(ni, oh->ntlv.name, oh->ntlv.set);
		if (cfg == NULL) {
			IPFW_UH_RUNLOCK(ch);
			return (ENOENT);
		}
		nat64clat_export_config(ch, cfg, uc);
		IPFW_UH_RUNLOCK(ch);
		return (0);
	}

	IPFW_UH_WLOCK(ch);
	cfg = nat64clat_find(ni, oh->ntlv.name, oh->ntlv.set);
	if (cfg == NULL) {
		IPFW_UH_WUNLOCK(ch);
		return (ENOENT);
	}

	/*
	 * For now allow to change only following values:
	 *  plat_prefix, plat_plen, clat_prefix, clat_plen, flags.
	 */
	flags = 0;
	if (uc->plat_plen != cfg->base.plat_plen ||
	    !IN6_ARE_ADDR_EQUAL(&uc->plat_prefix, &cfg->base.plat_prefix)) {
		if (nat64_check_prefix6(&uc->plat_prefix, uc->plat_plen) != 0) {
			IPFW_UH_WUNLOCK(ch);
			return (EINVAL);
		}
		flags |= NAT64_PLATPFX;
	}

	if (uc->clat_plen != cfg->base.clat_plen ||
	    !IN6_ARE_ADDR_EQUAL(&uc->clat_prefix, &cfg->base.clat_prefix)) {
		if (nat64_check_prefix6(&uc->clat_prefix, uc->clat_plen) != 0) {
			IPFW_UH_WUNLOCK(ch);
			return (EINVAL);
		}
		flags |= NAT64_CLATPFX;
	}

	if (flags != 0) {
		IPFW_WLOCK(ch);
		if (flags & NAT64_PLATPFX) {
			cfg->base.plat_prefix = uc->plat_prefix;
			cfg->base.plat_plen = uc->plat_plen;
		}
		if (flags & NAT64_CLATPFX) {
			cfg->base.clat_prefix = uc->clat_prefix;
			cfg->base.clat_plen = uc->clat_plen;
		}
		IPFW_WUNLOCK(ch);
	}

	cfg->base.flags &= ~NAT64CLAT_FLAGSMASK;
	cfg->base.flags |= uc->flags & NAT64CLAT_FLAGSMASK;

	IPFW_UH_WUNLOCK(ch);
	return (0);
}