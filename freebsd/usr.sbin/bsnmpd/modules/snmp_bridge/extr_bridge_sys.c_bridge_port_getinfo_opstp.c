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
typedef  int /*<<< orphan*/  uint16_t ;
struct ifbpstpreq {int /*<<< orphan*/  ifbp_design_port; int /*<<< orphan*/  ifbp_design_bridge; int /*<<< orphan*/  ifbp_design_root; int /*<<< orphan*/  ifbp_design_cost; int /*<<< orphan*/  ifbp_fwd_trans; } ;
struct bridge_port {int /*<<< orphan*/  design_port; int /*<<< orphan*/  design_bridge; int /*<<< orphan*/  design_root; int /*<<< orphan*/  design_cost; int /*<<< orphan*/  fwd_trans; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dot1dStpPortEnable_enabled ; 
 int /*<<< orphan*/  snmp_uint64_to_bridgeid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bridge_port_getinfo_opstp(struct ifbpstpreq *bp_stp, struct bridge_port *bp)
{
	bp->enable = dot1dStpPortEnable_enabled;
	bp->fwd_trans = bp_stp->ifbp_fwd_trans;
	bp->design_cost = bp_stp->ifbp_design_cost;
	snmp_uint64_to_bridgeid(bp_stp->ifbp_design_root, bp->design_root);
	snmp_uint64_to_bridgeid(bp_stp->ifbp_design_bridge, bp->design_bridge);
	bcopy(&(bp_stp->ifbp_design_port), &(bp->design_port),
	    sizeof(uint16_t));
}