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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;
struct TYPE_2__ {int counterselect; int symbolerrors; int linkrecovers; int linkdowned; int rcverrors; int rcvremotephyerrors; int rcvswrelayerrors; int xmtdiscards; int xmtconstrainterrors; int rcvconstrainterrors; int linkintegrityerrors; int excbufoverrunerrors; int qp1dropped; int vl15dropped; int xmtdata; int rcvdata; int xmtpkts; int rcvpkts; int xmtwait; } ;

/* Variables and functions */
 int ALL_PORTS ; 
 int /*<<< orphan*/  IB_PC_COUNTER_SELECT_F ; 
 int /*<<< orphan*/  IB_PC_ERR_EXCESS_OVR_F ; 
 int /*<<< orphan*/  IB_PC_ERR_LOCALINTEG_F ; 
 int /*<<< orphan*/  IB_PC_ERR_PHYSRCV_F ; 
 int /*<<< orphan*/  IB_PC_ERR_RCVCONSTR_F ; 
 int /*<<< orphan*/  IB_PC_ERR_RCV_F ; 
 int /*<<< orphan*/  IB_PC_ERR_SWITCH_REL_F ; 
 int /*<<< orphan*/  IB_PC_ERR_SYM_F ; 
 int /*<<< orphan*/  IB_PC_ERR_XMTCONSTR_F ; 
 int /*<<< orphan*/  IB_PC_LINK_DOWNED_F ; 
 int /*<<< orphan*/  IB_PC_LINK_RECOVERS_F ; 
 int /*<<< orphan*/  IB_PC_PORT_SELECT_F ; 
 int /*<<< orphan*/  IB_PC_QP1_DROP_F ; 
 int /*<<< orphan*/  IB_PC_RCV_BYTES_F ; 
 int /*<<< orphan*/  IB_PC_RCV_PKTS_F ; 
 int /*<<< orphan*/  IB_PC_VL15_DROPPED_F ; 
 int /*<<< orphan*/  IB_PC_XMT_BYTES_F ; 
 int /*<<< orphan*/  IB_PC_XMT_DISCARDS_F ; 
 int /*<<< orphan*/  IB_PC_XMT_PKTS_F ; 
 int /*<<< orphan*/  IB_PC_XMT_WAIT_F ; 
 int /*<<< orphan*/  mad_dump_perfcounters (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mad_encode_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pc ; 
 TYPE_1__ perf_count ; 
 char* portid2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,char*) ; 

__attribute__((used)) static void output_aggregate_perfcounters(ib_portid_t * portid,
					  uint16_t cap_mask)
{
	char buf[1024];
	uint32_t val = ALL_PORTS;

	/* set port_select to 255 to emulate AllPortSelect */
	mad_encode_field(pc, IB_PC_PORT_SELECT_F, &val);
	mad_encode_field(pc, IB_PC_COUNTER_SELECT_F, &perf_count.counterselect);
	mad_encode_field(pc, IB_PC_ERR_SYM_F, &perf_count.symbolerrors);
	mad_encode_field(pc, IB_PC_LINK_RECOVERS_F, &perf_count.linkrecovers);
	mad_encode_field(pc, IB_PC_LINK_DOWNED_F, &perf_count.linkdowned);
	mad_encode_field(pc, IB_PC_ERR_RCV_F, &perf_count.rcverrors);
	mad_encode_field(pc, IB_PC_ERR_PHYSRCV_F,
			 &perf_count.rcvremotephyerrors);
	mad_encode_field(pc, IB_PC_ERR_SWITCH_REL_F,
			 &perf_count.rcvswrelayerrors);
	mad_encode_field(pc, IB_PC_XMT_DISCARDS_F, &perf_count.xmtdiscards);
	mad_encode_field(pc, IB_PC_ERR_XMTCONSTR_F,
			 &perf_count.xmtconstrainterrors);
	mad_encode_field(pc, IB_PC_ERR_RCVCONSTR_F,
			 &perf_count.rcvconstrainterrors);
	mad_encode_field(pc, IB_PC_ERR_LOCALINTEG_F,
			 &perf_count.linkintegrityerrors);
	mad_encode_field(pc, IB_PC_ERR_EXCESS_OVR_F,
			 &perf_count.excbufoverrunerrors);
#ifdef HAVE_IB_PC_QP1_DROP_F
	mad_encode_field(pc, IB_PC_QP1_DROP_F, &perf_count.qp1dropped);
#endif
	mad_encode_field(pc, IB_PC_VL15_DROPPED_F, &perf_count.vl15dropped);
	mad_encode_field(pc, IB_PC_XMT_BYTES_F, &perf_count.xmtdata);
	mad_encode_field(pc, IB_PC_RCV_BYTES_F, &perf_count.rcvdata);
	mad_encode_field(pc, IB_PC_XMT_PKTS_F, &perf_count.xmtpkts);
	mad_encode_field(pc, IB_PC_RCV_PKTS_F, &perf_count.rcvpkts);
	mad_encode_field(pc, IB_PC_XMT_WAIT_F, &perf_count.xmtwait);

	mad_dump_perfcounters(buf, sizeof buf, pc, sizeof pc);

	printf("# Port counters: %s port %d (CapMask: 0x%02X)\n%s",
	       portid2str(portid), ALL_PORTS, ntohs(cap_mask), buf);
}