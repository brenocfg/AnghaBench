#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_SRV (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_DEL_OBJ_REWRITER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPFW_DEL_SOPT_HANDLER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPFW_TLV_NAT64LSN_NAME ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 scalar_t__ V_nat64lsn_eid ; 
 int /*<<< orphan*/  destroy_config_cb ; 
 int /*<<< orphan*/  ipfw_del_eaction (struct ip_fw_chain*,scalar_t__) ; 
 int /*<<< orphan*/  ipfw_objhash_foreach_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip_fw_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nat64lsn_uninit_internal () ; 
 int /*<<< orphan*/  opcodes ; 
 int /*<<< orphan*/  scodes ; 

void
nat64lsn_uninit(struct ip_fw_chain *ch, int last)
{

	IPFW_DEL_OBJ_REWRITER(last, opcodes);
	IPFW_DEL_SOPT_HANDLER(last, scodes);
	ipfw_del_eaction(ch, V_nat64lsn_eid);
	/*
	 * Since we already have deregistered external action,
	 * our named objects become unaccessible via rules, because
	 * all rules were truncated by ipfw_del_eaction().
	 * So, we can unlink and destroy our named objects without holding
	 * IPFW_WLOCK().
	 */
	IPFW_UH_WLOCK(ch);
	ipfw_objhash_foreach_type(CHAIN_TO_SRV(ch), destroy_config_cb, ch,
	    IPFW_TLV_NAT64LSN_NAME);
	V_nat64lsn_eid = 0;
	IPFW_UH_WUNLOCK(ch);
	if (last != 0)
		nat64lsn_uninit_internal();
}