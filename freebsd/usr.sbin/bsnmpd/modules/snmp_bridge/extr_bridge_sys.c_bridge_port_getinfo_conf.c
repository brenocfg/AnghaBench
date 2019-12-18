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
struct ifbreq {int ifbr_ifsflags; scalar_t__ ifbr_path_cost; int /*<<< orphan*/  ifbr_priority; int /*<<< orphan*/  ifbr_state; } ;
struct bridge_port {void* oper_ptp; int /*<<< orphan*/  admin_ptp; void* oper_edge; void* admin_edge; void* priv_set; int /*<<< orphan*/  span_enable; int /*<<< orphan*/  enable; scalar_t__ path_cost; scalar_t__ admin_path_cost; int /*<<< orphan*/  priority; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int IFBIF_BSTP_ADMCOST ; 
 int IFBIF_BSTP_ADMEDGE ; 
 int IFBIF_BSTP_AUTOPTP ; 
 int IFBIF_BSTP_EDGE ; 
 int IFBIF_BSTP_PTP ; 
 int IFBIF_PRIVATE ; 
 int IFBIF_SPAN ; 
 int IFBIF_STP ; 
 int /*<<< orphan*/  StpPortAdminPointToPointType_auto ; 
 int /*<<< orphan*/  StpPortAdminPointToPointType_forceFalse ; 
 int /*<<< orphan*/  StpPortAdminPointToPointType_forceTrue ; 
 void* TruthValue_false ; 
 void* TruthValue_true ; 
 int /*<<< orphan*/  begemotBridgeBaseSpanEnabled_disabled ; 
 int /*<<< orphan*/  begemotBridgeBaseSpanEnabled_enabled ; 
 int /*<<< orphan*/  dot1dStpPortEnable_disabled ; 
 int /*<<< orphan*/  dot1dStpPortEnable_enabled ; 
 int /*<<< orphan*/  state2snmp_st (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bridge_port_getinfo_conf(struct ifbreq *k_info, struct bridge_port *bp)
{
	bp->state = state2snmp_st(k_info->ifbr_state);
	bp->priority = k_info->ifbr_priority;

	/*
	 * RFC 4188:
	 * "New implementations should support dot1dStpPortPathCost32.
	 * If the port path costs exceeds the maximum value of this
	 * object then this object should report the maximum value,
	 * namely 65535.  Applications should try to read the
	 * dot1dStpPortPathCost32 object if this object reports
	 * the maximum value."
	 */

	if (k_info->ifbr_ifsflags & IFBIF_BSTP_ADMCOST)
		bp->admin_path_cost = k_info->ifbr_path_cost;
	else
		bp->admin_path_cost = 0;

	bp->path_cost = k_info->ifbr_path_cost;

	if (k_info->ifbr_ifsflags & IFBIF_STP)
		bp->enable = dot1dStpPortEnable_enabled;
	else
		bp->enable = dot1dStpPortEnable_disabled;

	/* Begemot Bridge MIB only. */
	if (k_info->ifbr_ifsflags & IFBIF_SPAN)
		bp->span_enable = begemotBridgeBaseSpanEnabled_enabled;
	else
		bp->span_enable = begemotBridgeBaseSpanEnabled_disabled;

	if (k_info->ifbr_ifsflags & IFBIF_PRIVATE)
		bp->priv_set = TruthValue_true;
	else
		bp->priv_set = TruthValue_false;

	if (k_info->ifbr_ifsflags & IFBIF_BSTP_ADMEDGE)
		bp->admin_edge = TruthValue_true;
	else
		bp->admin_edge = TruthValue_false;

	if (k_info->ifbr_ifsflags & IFBIF_BSTP_EDGE)
		bp->oper_edge = TruthValue_true;
	else
		bp->oper_edge = TruthValue_false;

	if (k_info->ifbr_ifsflags & IFBIF_BSTP_AUTOPTP) {
		bp->admin_ptp = StpPortAdminPointToPointType_auto;
		if (k_info->ifbr_ifsflags & IFBIF_BSTP_PTP)
			bp->oper_ptp = TruthValue_true;
		else
			bp->oper_ptp = TruthValue_false;
	} else if (k_info->ifbr_ifsflags & IFBIF_BSTP_PTP) {
		bp->admin_ptp = StpPortAdminPointToPointType_forceTrue;
		bp->oper_ptp = TruthValue_true;
	} else {
		bp->admin_ptp = StpPortAdminPointToPointType_forceFalse;
		bp->oper_ptp = TruthValue_false;
	}
}