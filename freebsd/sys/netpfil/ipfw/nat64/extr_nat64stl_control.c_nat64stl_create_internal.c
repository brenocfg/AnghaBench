#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  kidx; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct nat64stl_cfg {TYPE_4__ no; TYPE_1__ base; int /*<<< orphan*/  map64; int /*<<< orphan*/  map46; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ntlv6; int /*<<< orphan*/  ntlv4; } ;
typedef  TYPE_2__ ipfw_nat64stl_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_SRV (struct ip_fw_chain*) ; 
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  NAT64STL_46T ; 
 int /*<<< orphan*/  NAT64STL_64T ; 
 int /*<<< orphan*/  NAT64STL_KIDX ; 
 int /*<<< orphan*/  ipfw_objhash_add (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ ipfw_objhash_alloc_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ipfw_ref_table (struct ip_fw_chain*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nat64stl_create_internal(struct ip_fw_chain *ch, struct nat64stl_cfg *cfg,
    ipfw_nat64stl_cfg *i)
{

	IPFW_UH_WLOCK_ASSERT(ch);

	if (ipfw_objhash_alloc_idx(CHAIN_TO_SRV(ch), &cfg->no.kidx) != 0)
		return (ENOSPC);
	cfg->base.flags |= NAT64STL_KIDX;

	if (ipfw_ref_table(ch, &i->ntlv4, &cfg->map46) != 0)
		return (EINVAL);
	cfg->base.flags |= NAT64STL_46T;

	if (ipfw_ref_table(ch, &i->ntlv6, &cfg->map64) != 0)
		return (EINVAL);
	cfg->base.flags |= NAT64STL_64T;

	ipfw_objhash_add(CHAIN_TO_SRV(ch), &cfg->no);

	return (0);
}