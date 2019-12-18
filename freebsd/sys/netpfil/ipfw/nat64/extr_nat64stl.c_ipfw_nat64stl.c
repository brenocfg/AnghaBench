#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct nat64stl_cfg {int /*<<< orphan*/  map64; int /*<<< orphan*/  map46; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_5__ {int addr_type; scalar_t__ proto; int /*<<< orphan*/  src_ip6; int /*<<< orphan*/  dst_ip; } ;
struct ip_fw_args {int /*<<< orphan*/ * m; TYPE_1__ f_id; } ;
struct in6_addr {int dummy; } ;
struct TYPE_6__ {scalar_t__ opcode; scalar_t__ arg1; } ;
typedef  TYPE_2__ ipfw_insn ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_RLOCK_ASSERT (struct ip_fw_chain*) ; 
 scalar_t__ IPPROTO_ICMPV6 ; 
 int IP_FW_NAT64 ; 
 int NAT64MFREE ; 
 int NAT64SKIP ; 
 struct nat64stl_cfg* NAT64_LOOKUP (struct ip_fw_chain*,TYPE_2__*) ; 
 scalar_t__ O_EXTERNAL_ACTION ; 
 scalar_t__ O_EXTERNAL_INSTANCE ; 
 scalar_t__ V_nat64stl_eid ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int ipfw_lookup_table (struct ip_fw_chain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int nat64stl_handle_icmp6 (struct ip_fw_chain*,struct nat64stl_cfg*,int /*<<< orphan*/ *) ; 
 int nat64stl_handle_ip4 (struct ip_fw_chain*,struct nat64stl_cfg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nat64stl_handle_ip6 (struct ip_fw_chain*,struct nat64stl_cfg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ipfw_nat64stl(struct ip_fw_chain *chain, struct ip_fw_args *args,
    ipfw_insn *cmd, int *done)
{
	ipfw_insn *icmd;
	struct nat64stl_cfg *cfg;
	in_addr_t dst4;
	uint32_t tablearg;
	int ret;

	IPFW_RLOCK_ASSERT(chain);

	*done = 0; /* try next rule if not matched */
	icmd = cmd + 1;
	if (cmd->opcode != O_EXTERNAL_ACTION ||
	    cmd->arg1 != V_nat64stl_eid ||
	    icmd->opcode != O_EXTERNAL_INSTANCE ||
	    (cfg = NAT64_LOOKUP(chain, icmd)) == NULL)
		return (0);

	switch (args->f_id.addr_type) {
	case 4:
		dst4 = htonl(args->f_id.dst_ip);
		ret = ipfw_lookup_table(chain, cfg->map46, sizeof(in_addr_t),
		    &dst4, &tablearg);
		break;
	case 6:
		ret = ipfw_lookup_table(chain, cfg->map64,
		    sizeof(struct in6_addr), &args->f_id.src_ip6, &tablearg);
		break;
	default:
		return (0);
	}
	if (ret == 0) {
		/*
		 * In case when packet is ICMPv6 message from an intermediate
		 * router, the source address of message will not match the
		 * addresses from our map64 table.
		 */
		if (args->f_id.proto != IPPROTO_ICMPV6)
			return (0);

		ret = nat64stl_handle_icmp6(chain, cfg, args->m);
	} else {
		if (args->f_id.addr_type == 4)
			ret = nat64stl_handle_ip4(chain, cfg, args->m,
			    tablearg);
		else
			ret = nat64stl_handle_ip6(chain, cfg, args->m,
			    tablearg);
	}
	if (ret == NAT64SKIP)
		return (0);

	*done = 1; /* terminate the search */
	if (ret == NAT64MFREE)
		m_freem(args->m);
	args->m = NULL;
	return (IP_FW_NAT64);
}