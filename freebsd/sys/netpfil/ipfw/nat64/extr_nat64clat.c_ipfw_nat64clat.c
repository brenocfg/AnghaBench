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
struct nat64clat_cfg {int dummy; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_5__ {int addr_type; scalar_t__ proto; } ;
struct ip_fw_args {int /*<<< orphan*/ * m; TYPE_1__ f_id; } ;
struct TYPE_6__ {scalar_t__ opcode; scalar_t__ arg1; } ;
typedef  TYPE_2__ ipfw_insn ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_RLOCK_ASSERT (struct ip_fw_chain*) ; 
 scalar_t__ IPPROTO_ICMPV6 ; 
 int IP_FW_NAT64 ; 
 int NAT64MFREE ; 
 int NAT64SKIP ; 
 struct nat64clat_cfg* NAT64_LOOKUP (struct ip_fw_chain*,TYPE_2__*) ; 
 scalar_t__ O_EXTERNAL_ACTION ; 
 scalar_t__ O_EXTERNAL_INSTANCE ; 
 scalar_t__ V_nat64clat_eid ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int nat64clat_handle_icmp6 (struct ip_fw_chain*,struct nat64clat_cfg*,int /*<<< orphan*/ *) ; 
 int nat64clat_handle_ip4 (struct ip_fw_chain*,struct nat64clat_cfg*,int /*<<< orphan*/ *) ; 
 int nat64clat_handle_ip6 (struct ip_fw_chain*,struct nat64clat_cfg*,int /*<<< orphan*/ *) ; 

int
ipfw_nat64clat(struct ip_fw_chain *chain, struct ip_fw_args *args,
    ipfw_insn *cmd, int *done)
{
	ipfw_insn *icmd;
	struct nat64clat_cfg *cfg;
	int ret;

	IPFW_RLOCK_ASSERT(chain);

	*done = 0; /* try next rule if not matched */
	icmd = cmd + 1;
	if (cmd->opcode != O_EXTERNAL_ACTION ||
	    cmd->arg1 != V_nat64clat_eid ||
	    icmd->opcode != O_EXTERNAL_INSTANCE ||
	    (cfg = NAT64_LOOKUP(chain, icmd)) == NULL)
		return (0);

	switch (args->f_id.addr_type) {
	case 4:
		ret = nat64clat_handle_ip4(chain, cfg, args->m);
		break;
	case 6:
		ret = nat64clat_handle_ip6(chain, cfg, args->m);
		break;
	default:
		return (0);
	}

	if (ret == NAT64SKIP) {
		/*
		 * In case when packet is ICMPv6 message from an intermediate
		 * router, the source address of message will not match the
		 * addresses from configured prefixes.
		 */
		if (args->f_id.proto != IPPROTO_ICMPV6)
			return (0);

		ret = nat64clat_handle_icmp6(chain, cfg, args->m);
	}

	if (ret == NAT64SKIP)
		return (0);

	*done = 1; /* terminate the search */
	if (ret == NAT64MFREE)
		m_freem(args->m);

	args->m = NULL;
	return (IP_FW_NAT64);
}