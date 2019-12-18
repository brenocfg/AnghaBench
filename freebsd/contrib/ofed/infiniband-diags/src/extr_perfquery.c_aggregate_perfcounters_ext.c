#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  void* uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  QP1Dropped; int /*<<< orphan*/  portXmitWait; int /*<<< orphan*/  VL15Dropped; int /*<<< orphan*/  excessiveBufferOverrunErrors; int /*<<< orphan*/  localLinkIntegrityErrors; int /*<<< orphan*/  portRcvConstraintErrors; int /*<<< orphan*/  portXmitConstraintErrors; int /*<<< orphan*/  portXmitDiscards; int /*<<< orphan*/  portRcvSwitchRelayErrors; int /*<<< orphan*/  portRcvRemotePhysicalErrors; int /*<<< orphan*/  portRcvErrors; int /*<<< orphan*/  linkDownedCounter; int /*<<< orphan*/  linkErrorRecoveryCounter; int /*<<< orphan*/  symbolErrorCounter; void* counterSelect2; int /*<<< orphan*/  portmulticastrcvpkts; int /*<<< orphan*/  portmulticastxmitpkits; int /*<<< orphan*/  portunicastrcvpkts; int /*<<< orphan*/  portunicastxmitpkts; int /*<<< orphan*/  portrcvpkts; int /*<<< orphan*/  portxmitpkts; int /*<<< orphan*/  portrcvdata; int /*<<< orphan*/  portxmitdata; void* counterselect; void* portselect; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_PC_EXT_COUNTER_SELECT2_F ; 
 int /*<<< orphan*/  IB_PC_EXT_COUNTER_SELECT_F ; 
 int /*<<< orphan*/  IB_PC_EXT_ERR_EXCESS_OVR_F ; 
 int /*<<< orphan*/  IB_PC_EXT_ERR_LOCALINTEG_F ; 
 int /*<<< orphan*/  IB_PC_EXT_ERR_PHYSRCV_F ; 
 int /*<<< orphan*/  IB_PC_EXT_ERR_RCVCONSTR_F ; 
 int /*<<< orphan*/  IB_PC_EXT_ERR_RCV_F ; 
 int /*<<< orphan*/  IB_PC_EXT_ERR_SWITCH_REL_F ; 
 int /*<<< orphan*/  IB_PC_EXT_ERR_SYM_F ; 
 int /*<<< orphan*/  IB_PC_EXT_ERR_XMTCONSTR_F ; 
 int /*<<< orphan*/  IB_PC_EXT_LINK_DOWNED_F ; 
 int /*<<< orphan*/  IB_PC_EXT_LINK_RECOVERS_F ; 
 int /*<<< orphan*/  IB_PC_EXT_PORT_SELECT_F ; 
 int /*<<< orphan*/  IB_PC_EXT_QP1_DROP_F ; 
 int /*<<< orphan*/  IB_PC_EXT_RCV_BYTES_F ; 
 int /*<<< orphan*/  IB_PC_EXT_RCV_MPKTS_F ; 
 int /*<<< orphan*/  IB_PC_EXT_RCV_PKTS_F ; 
 int /*<<< orphan*/  IB_PC_EXT_RCV_UPKTS_F ; 
 int /*<<< orphan*/  IB_PC_EXT_VL15_DROPPED_F ; 
 int /*<<< orphan*/  IB_PC_EXT_XMT_BYTES_F ; 
 int /*<<< orphan*/  IB_PC_EXT_XMT_DISCARDS_F ; 
 int /*<<< orphan*/  IB_PC_EXT_XMT_MPKTS_F ; 
 int /*<<< orphan*/  IB_PC_EXT_XMT_PKTS_F ; 
 int /*<<< orphan*/  IB_PC_EXT_XMT_UPKTS_F ; 
 int /*<<< orphan*/  IB_PC_EXT_XMT_WAIT_F ; 
 int IB_PM_EXT_WIDTH_SUPPORTED ; 
 int IB_PM_IS_ADDL_PORT_CTRS_EXT_SUP ; 
 int /*<<< orphan*/  aggregate_64bit (int /*<<< orphan*/ *,void*) ; 
 int htonl (void*) ; 
 int /*<<< orphan*/  mad_decode_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pc ; 
 TYPE_1__ perf_count_ext ; 

__attribute__((used)) static void aggregate_perfcounters_ext(uint16_t cap_mask, uint32_t cap_mask2)
{
	uint32_t val;
	uint64_t val64;

	mad_decode_field(pc, IB_PC_EXT_PORT_SELECT_F, &val);
	perf_count_ext.portselect = val;
	mad_decode_field(pc, IB_PC_EXT_COUNTER_SELECT_F, &val);
	perf_count_ext.counterselect = val;
	mad_decode_field(pc, IB_PC_EXT_XMT_BYTES_F, &val64);
	aggregate_64bit(&perf_count_ext.portxmitdata, val64);
	mad_decode_field(pc, IB_PC_EXT_RCV_BYTES_F, &val64);
	aggregate_64bit(&perf_count_ext.portrcvdata, val64);
	mad_decode_field(pc, IB_PC_EXT_XMT_PKTS_F, &val64);
	aggregate_64bit(&perf_count_ext.portxmitpkts, val64);
	mad_decode_field(pc, IB_PC_EXT_RCV_PKTS_F, &val64);
	aggregate_64bit(&perf_count_ext.portrcvpkts, val64);

	if (cap_mask & IB_PM_EXT_WIDTH_SUPPORTED) {
		mad_decode_field(pc, IB_PC_EXT_XMT_UPKTS_F, &val64);
		aggregate_64bit(&perf_count_ext.portunicastxmitpkts, val64);
		mad_decode_field(pc, IB_PC_EXT_RCV_UPKTS_F, &val64);
		aggregate_64bit(&perf_count_ext.portunicastrcvpkts, val64);
		mad_decode_field(pc, IB_PC_EXT_XMT_MPKTS_F, &val64);
		aggregate_64bit(&perf_count_ext.portmulticastxmitpkits, val64);
		mad_decode_field(pc, IB_PC_EXT_RCV_MPKTS_F, &val64);
		aggregate_64bit(&perf_count_ext.portmulticastrcvpkts, val64);
	}

	if (htonl(cap_mask2) & IB_PM_IS_ADDL_PORT_CTRS_EXT_SUP) {
		mad_decode_field(pc, IB_PC_EXT_COUNTER_SELECT2_F, &val);
		perf_count_ext.counterSelect2 = val;
		mad_decode_field(pc, IB_PC_EXT_ERR_SYM_F, &val64);
		aggregate_64bit(&perf_count_ext.symbolErrorCounter, val64);
		mad_decode_field(pc, IB_PC_EXT_LINK_RECOVERS_F, &val64);
		aggregate_64bit(&perf_count_ext.linkErrorRecoveryCounter, val64);
		mad_decode_field(pc, IB_PC_EXT_LINK_DOWNED_F, &val64);
		aggregate_64bit(&perf_count_ext.linkDownedCounter, val64);
		mad_decode_field(pc, IB_PC_EXT_ERR_RCV_F, &val64);
		aggregate_64bit(&perf_count_ext.portRcvErrors, val64);
		mad_decode_field(pc, IB_PC_EXT_ERR_PHYSRCV_F, &val64);
		aggregate_64bit(&perf_count_ext.portRcvRemotePhysicalErrors, val64);
		mad_decode_field(pc, IB_PC_EXT_ERR_SWITCH_REL_F, &val64);
		aggregate_64bit(&perf_count_ext.portRcvSwitchRelayErrors, val64);
		mad_decode_field(pc, IB_PC_EXT_XMT_DISCARDS_F, &val64);
		aggregate_64bit(&perf_count_ext.portXmitDiscards, val64);
		mad_decode_field(pc, IB_PC_EXT_ERR_XMTCONSTR_F, &val64);
		aggregate_64bit(&perf_count_ext.portXmitConstraintErrors, val64);
		mad_decode_field(pc, IB_PC_EXT_ERR_RCVCONSTR_F, &val64);
		aggregate_64bit(&perf_count_ext.portRcvConstraintErrors, val64);
		mad_decode_field(pc, IB_PC_EXT_ERR_LOCALINTEG_F, &val64);
		aggregate_64bit(&perf_count_ext.localLinkIntegrityErrors, val64);
		mad_decode_field(pc, IB_PC_EXT_ERR_EXCESS_OVR_F, &val64);
		aggregate_64bit(&perf_count_ext.excessiveBufferOverrunErrors, val64);
		mad_decode_field(pc, IB_PC_EXT_VL15_DROPPED_F, &val64);
		aggregate_64bit(&perf_count_ext.VL15Dropped, val64);
		mad_decode_field(pc, IB_PC_EXT_XMT_WAIT_F, &val64);
		aggregate_64bit(&perf_count_ext.portXmitWait, val64);
		mad_decode_field(pc, IB_PC_EXT_QP1_DROP_F, &val64);
		aggregate_64bit(&perf_count_ext.QP1Dropped, val64);
	}
}