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
typedef  void* uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  xmtwait; int /*<<< orphan*/  rcvpkts; int /*<<< orphan*/  xmtpkts; int /*<<< orphan*/  rcvdata; int /*<<< orphan*/  xmtdata; int /*<<< orphan*/  vl15dropped; int /*<<< orphan*/  qp1dropped; int /*<<< orphan*/  excbufoverrunerrors; int /*<<< orphan*/  linkintegrityerrors; int /*<<< orphan*/  rcvconstrainterrors; int /*<<< orphan*/  xmtconstrainterrors; int /*<<< orphan*/  xmtdiscards; int /*<<< orphan*/  rcvswrelayerrors; int /*<<< orphan*/  rcvremotephyerrors; int /*<<< orphan*/  rcverrors; int /*<<< orphan*/  linkdowned; int /*<<< orphan*/  linkrecovers; int /*<<< orphan*/  symbolerrors; void* counterselect; void* portselect; } ;

/* Variables and functions */
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
 int /*<<< orphan*/  aggregate_16bit (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  aggregate_32bit (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  aggregate_4bit (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  aggregate_8bit (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  mad_decode_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pc ; 
 TYPE_1__ perf_count ; 

__attribute__((used)) static void aggregate_perfcounters(void)
{
	uint32_t val;

	mad_decode_field(pc, IB_PC_PORT_SELECT_F, &val);
	perf_count.portselect = val;
	mad_decode_field(pc, IB_PC_COUNTER_SELECT_F, &val);
	perf_count.counterselect = val;
	mad_decode_field(pc, IB_PC_ERR_SYM_F, &val);
	aggregate_16bit(&perf_count.symbolerrors, val);
	mad_decode_field(pc, IB_PC_LINK_RECOVERS_F, &val);
	aggregate_8bit(&perf_count.linkrecovers, val);
	mad_decode_field(pc, IB_PC_LINK_DOWNED_F, &val);
	aggregate_8bit(&perf_count.linkdowned, val);
	mad_decode_field(pc, IB_PC_ERR_RCV_F, &val);
	aggregate_16bit(&perf_count.rcverrors, val);
	mad_decode_field(pc, IB_PC_ERR_PHYSRCV_F, &val);
	aggregate_16bit(&perf_count.rcvremotephyerrors, val);
	mad_decode_field(pc, IB_PC_ERR_SWITCH_REL_F, &val);
	aggregate_16bit(&perf_count.rcvswrelayerrors, val);
	mad_decode_field(pc, IB_PC_XMT_DISCARDS_F, &val);
	aggregate_16bit(&perf_count.xmtdiscards, val);
	mad_decode_field(pc, IB_PC_ERR_XMTCONSTR_F, &val);
	aggregate_8bit(&perf_count.xmtconstrainterrors, val);
	mad_decode_field(pc, IB_PC_ERR_RCVCONSTR_F, &val);
	aggregate_8bit(&perf_count.rcvconstrainterrors, val);
	mad_decode_field(pc, IB_PC_ERR_LOCALINTEG_F, &val);
	aggregate_4bit(&perf_count.linkintegrityerrors, val);
	mad_decode_field(pc, IB_PC_ERR_EXCESS_OVR_F, &val);
	aggregate_4bit(&perf_count.excbufoverrunerrors, val);
#ifdef HAVE_IB_PC_QP1_DROP_F
	mad_decode_field(pc, IB_PC_QP1_DROP_F, &val);
	aggregate_16bit(&perf_count.qp1dropped, val);
#endif
	mad_decode_field(pc, IB_PC_VL15_DROPPED_F, &val);
	aggregate_16bit(&perf_count.vl15dropped, val);
	mad_decode_field(pc, IB_PC_XMT_BYTES_F, &val);
	aggregate_32bit(&perf_count.xmtdata, val);
	mad_decode_field(pc, IB_PC_RCV_BYTES_F, &val);
	aggregate_32bit(&perf_count.rcvdata, val);
	mad_decode_field(pc, IB_PC_XMT_PKTS_F, &val);
	aggregate_32bit(&perf_count.xmtpkts, val);
	mad_decode_field(pc, IB_PC_RCV_PKTS_F, &val);
	aggregate_32bit(&perf_count.rcvpkts, val);
	mad_decode_field(pc, IB_PC_XMT_WAIT_F, &val);
	aggregate_32bit(&perf_count.xmtwait, val);
}