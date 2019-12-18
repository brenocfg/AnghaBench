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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int counterselect; int portxmitdata; int portrcvdata; int portxmitpkts; int portrcvpkts; int portunicastxmitpkts; int portunicastrcvpkts; int portmulticastxmitpkits; int portmulticastrcvpkts; int counterSelect2; int symbolErrorCounter; int linkErrorRecoveryCounter; int linkDownedCounter; int portRcvErrors; int portRcvRemotePhysicalErrors; int portRcvSwitchRelayErrors; int portXmitDiscards; int portXmitConstraintErrors; int portRcvConstraintErrors; int localLinkIntegrityErrors; int excessiveBufferOverrunErrors; int VL15Dropped; int portXmitWait; int QP1Dropped; } ;

/* Variables and functions */
 int ALL_PORTS ; 
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
 int htonl (int) ; 
 int /*<<< orphan*/  mad_dump_perfcounters_ext (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mad_encode_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int ntohs (int) ; 
 int /*<<< orphan*/  pc ; 
 TYPE_1__ perf_count_ext ; 
 char* portid2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,char*) ; 

__attribute__((used)) static void output_aggregate_perfcounters_ext(ib_portid_t * portid,
					      uint16_t cap_mask, uint32_t cap_mask2)
{
	char buf[1536];
	uint32_t val = ALL_PORTS;

	memset(buf, 0, sizeof(buf));

	/* set port_select to 255 to emulate AllPortSelect */
	mad_encode_field(pc, IB_PC_EXT_PORT_SELECT_F, &val);
	mad_encode_field(pc, IB_PC_EXT_COUNTER_SELECT_F,
			 &perf_count_ext.counterselect);
	mad_encode_field(pc, IB_PC_EXT_XMT_BYTES_F,
			 &perf_count_ext.portxmitdata);
	mad_encode_field(pc, IB_PC_EXT_RCV_BYTES_F,
			 &perf_count_ext.portrcvdata);
	mad_encode_field(pc, IB_PC_EXT_XMT_PKTS_F,
			 &perf_count_ext.portxmitpkts);
	mad_encode_field(pc, IB_PC_EXT_RCV_PKTS_F, &perf_count_ext.portrcvpkts);

	if (cap_mask & IB_PM_EXT_WIDTH_SUPPORTED) {
		mad_encode_field(pc, IB_PC_EXT_XMT_UPKTS_F,
				 &perf_count_ext.portunicastxmitpkts);
		mad_encode_field(pc, IB_PC_EXT_RCV_UPKTS_F,
				 &perf_count_ext.portunicastrcvpkts);
		mad_encode_field(pc, IB_PC_EXT_XMT_MPKTS_F,
				 &perf_count_ext.portmulticastxmitpkits);
		mad_encode_field(pc, IB_PC_EXT_RCV_MPKTS_F,
				 &perf_count_ext.portmulticastrcvpkts);
	}

	if (htonl(cap_mask2) & IB_PM_IS_ADDL_PORT_CTRS_EXT_SUP) {
		mad_encode_field(pc, IB_PC_EXT_COUNTER_SELECT2_F,
				 &perf_count_ext.counterSelect2);
		mad_encode_field(pc, IB_PC_EXT_ERR_SYM_F,
				 &perf_count_ext.symbolErrorCounter);
		mad_encode_field(pc, IB_PC_EXT_LINK_RECOVERS_F,
				 &perf_count_ext.linkErrorRecoveryCounter);
		mad_encode_field(pc, IB_PC_EXT_LINK_DOWNED_F,
				 &perf_count_ext.linkDownedCounter);
		mad_encode_field(pc, IB_PC_EXT_ERR_RCV_F,
				 &perf_count_ext.portRcvErrors);
		mad_encode_field(pc, IB_PC_EXT_ERR_PHYSRCV_F,
				 &perf_count_ext.portRcvRemotePhysicalErrors);
		mad_encode_field(pc, IB_PC_EXT_ERR_SWITCH_REL_F,
				 &perf_count_ext.portRcvSwitchRelayErrors);
		mad_encode_field(pc, IB_PC_EXT_XMT_DISCARDS_F,
				 &perf_count_ext.portXmitDiscards);
		mad_encode_field(pc, IB_PC_EXT_ERR_XMTCONSTR_F,
				 &perf_count_ext.portXmitConstraintErrors);
		mad_encode_field(pc, IB_PC_EXT_ERR_RCVCONSTR_F,
				 &perf_count_ext.portRcvConstraintErrors);
		mad_encode_field(pc, IB_PC_EXT_ERR_LOCALINTEG_F,
				 &perf_count_ext.localLinkIntegrityErrors);
		mad_encode_field(pc, IB_PC_EXT_ERR_EXCESS_OVR_F,
				 &perf_count_ext.excessiveBufferOverrunErrors);
		mad_encode_field(pc, IB_PC_EXT_VL15_DROPPED_F,
				 &perf_count_ext.VL15Dropped);
		mad_encode_field(pc, IB_PC_EXT_XMT_WAIT_F,
				 &perf_count_ext.portXmitWait);
		mad_encode_field(pc, IB_PC_EXT_QP1_DROP_F,
				 &perf_count_ext.QP1Dropped);
	}

	mad_dump_perfcounters_ext(buf, sizeof buf, pc, sizeof pc);

	printf("# Port extended counters: %s port %d (CapMask: 0x%02X CapMask2: 0x%07X)\n%s",
	       portid2str(portid), ALL_PORTS, ntohs(cap_mask), cap_mask2, buf);
}