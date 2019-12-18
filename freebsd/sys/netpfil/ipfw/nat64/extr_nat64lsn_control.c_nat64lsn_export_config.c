#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  set; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  plat_plen; int /*<<< orphan*/  plat_prefix; } ;
struct nat64lsn_cfg {TYPE_3__ no; TYPE_2__ base; int /*<<< orphan*/  plen4; int /*<<< orphan*/  prefix4; int /*<<< orphan*/  st_icmp_ttl; int /*<<< orphan*/  st_udp_ttl; int /*<<< orphan*/  st_estab_ttl; int /*<<< orphan*/  st_close_ttl; int /*<<< orphan*/  st_syn_ttl; int /*<<< orphan*/  pg_delete_delay; int /*<<< orphan*/  host_delete_delay; int /*<<< orphan*/  jmaxlen; int /*<<< orphan*/  states_chunks; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  set; int /*<<< orphan*/  plen6; int /*<<< orphan*/  plen4; int /*<<< orphan*/  prefix6; TYPE_1__ prefix4; int /*<<< orphan*/  st_icmp_ttl; int /*<<< orphan*/  st_udp_ttl; int /*<<< orphan*/  st_estab_ttl; int /*<<< orphan*/  st_close_ttl; int /*<<< orphan*/  st_syn_ttl; int /*<<< orphan*/  pg_delete_delay; int /*<<< orphan*/  nh_delete_delay; int /*<<< orphan*/  jmaxlen; int /*<<< orphan*/  states_chunks; } ;
typedef  TYPE_4__ ipfw_nat64lsn_cfg ;

/* Variables and functions */
 int NAT64LSN_FLAGSMASK ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nat64lsn_export_config(struct ip_fw_chain *ch, struct nat64lsn_cfg *cfg,
    ipfw_nat64lsn_cfg *uc)
{

	uc->flags = cfg->base.flags & NAT64LSN_FLAGSMASK;
	uc->states_chunks = cfg->states_chunks;
	uc->jmaxlen = cfg->jmaxlen;
	uc->nh_delete_delay = cfg->host_delete_delay;
	uc->pg_delete_delay = cfg->pg_delete_delay;
	uc->st_syn_ttl = cfg->st_syn_ttl;
	uc->st_close_ttl = cfg->st_close_ttl;
	uc->st_estab_ttl = cfg->st_estab_ttl;
	uc->st_udp_ttl = cfg->st_udp_ttl;
	uc->st_icmp_ttl = cfg->st_icmp_ttl;
	uc->prefix4.s_addr = htonl(cfg->prefix4);
	uc->prefix6 = cfg->base.plat_prefix;
	uc->plen4 = cfg->plen4;
	uc->plen6 = cfg->base.plat_plen;
	uc->set = cfg->no.set;
	strlcpy(uc->name, cfg->no.name, sizeof(uc->name));
}