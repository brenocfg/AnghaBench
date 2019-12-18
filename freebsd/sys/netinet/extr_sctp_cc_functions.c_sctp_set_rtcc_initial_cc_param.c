#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int use_precise_time; } ;
struct sctp_tcb {int rport; TYPE_2__* sctp_ep; TYPE_1__ asoc; } ;
struct TYPE_7__ {scalar_t__ last_step_state; scalar_t__ step_cnt; void* use_dccc_ecn; void* steady_step; void* ret_from_eq; scalar_t__ tls_needs_set; scalar_t__ bw_bytes; scalar_t__ bw_tot_time; scalar_t__ bw_bytes_at_last_rttc; scalar_t__ vol_reduce; scalar_t__ lbw; scalar_t__ cwnd_at_bw_set; scalar_t__ lbw_rtt; } ;
struct TYPE_8__ {TYPE_3__ rtcc; } ;
struct sctp_nets {int rtt; TYPE_4__ cc_mod; scalar_t__ cwnd; } ;
struct TYPE_6__ {scalar_t__ sctp_lport; } ;

/* Variables and functions */
 void* SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDT_PROBE5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_nets*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cwnd ; 
 int /*<<< orphan*/  rttvar ; 
 int /*<<< orphan*/  sctp ; 
 int /*<<< orphan*/  sctp_rttvar_eqret ; 
 int /*<<< orphan*/  sctp_set_initial_cc_param (struct sctp_tcb*,struct sctp_nets*) ; 
 int /*<<< orphan*/  sctp_steady_step ; 
 int /*<<< orphan*/  sctp_use_dccc_ecn ; 

__attribute__((used)) static void
sctp_set_rtcc_initial_cc_param(struct sctp_tcb *stcb,
    struct sctp_nets *net)
{
	uint64_t vtag, probepoint;

	sctp_set_initial_cc_param(stcb, net);
	stcb->asoc.use_precise_time = 1;
	probepoint = (((uint64_t)net->cwnd) << 32);
	probepoint |= ((9 << 16) | 0);
	vtag = (net->rtt << 32) |
	    (((uint32_t)(stcb->sctp_ep->sctp_lport)) << 16) |
	    (stcb->rport);
	SDT_PROBE5(sctp, cwnd, net, rttvar,
	    vtag,
	    0,
	    0,
	    0,
	    probepoint);
	net->cc_mod.rtcc.lbw_rtt = 0;
	net->cc_mod.rtcc.cwnd_at_bw_set = 0;
	net->cc_mod.rtcc.vol_reduce = 0;
	net->cc_mod.rtcc.lbw = 0;
	net->cc_mod.rtcc.vol_reduce = 0;
	net->cc_mod.rtcc.bw_bytes_at_last_rttc = 0;
	net->cc_mod.rtcc.bw_tot_time = 0;
	net->cc_mod.rtcc.bw_bytes = 0;
	net->cc_mod.rtcc.tls_needs_set = 0;
	net->cc_mod.rtcc.ret_from_eq = SCTP_BASE_SYSCTL(sctp_rttvar_eqret);
	net->cc_mod.rtcc.steady_step = SCTP_BASE_SYSCTL(sctp_steady_step);
	net->cc_mod.rtcc.use_dccc_ecn = SCTP_BASE_SYSCTL(sctp_use_dccc_ecn);
	net->cc_mod.rtcc.step_cnt = 0;
	net->cc_mod.rtcc.last_step_state = 0;


}