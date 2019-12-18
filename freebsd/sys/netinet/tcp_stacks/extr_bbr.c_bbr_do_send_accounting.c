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
struct tcpcb {int t_flags; int t_sndtlpbyte; int /*<<< orphan*/  t_stats; int /*<<< orphan*/  t_sndrexmitpack; int /*<<< orphan*/  t_sndtlppack; } ;
struct tcp_bbr {size_t rc_bbr_state; } ;
struct bbr_sendmap {int r_flags; size_t r_bbr_state; } ;
typedef  int int32_t ;

/* Variables and functions */
 size_t BBR_STATE_PROBE_BW ; 
 int BBR_TLP ; 
 int /*<<< orphan*/  TCPSTAT_ADD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int TF_FORCEDATA ; 
 int /*<<< orphan*/  VOI_TCP_RETXPB ; 
 int /*<<< orphan*/  VOI_TCP_TXPB ; 
 int /*<<< orphan*/  bbr_do_error_accounting (struct tcpcb*,struct tcp_bbr*,struct bbr_sendmap*,int,int) ; 
 int /*<<< orphan*/ * bbr_state_lost ; 
 int /*<<< orphan*/ * bbr_state_resend ; 
 int bbr_state_val (struct tcp_bbr*) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stats_voi_update_abs_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stats_voi_update_abs_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcps_sndbyte ; 
 int /*<<< orphan*/  tcps_sndpack ; 
 int /*<<< orphan*/  tcps_sndprobe ; 
 int /*<<< orphan*/  tcps_sndrexmitbyte ; 
 int /*<<< orphan*/  tcps_sndrexmitpack ; 
 int /*<<< orphan*/  tcps_tlpresend_bytes ; 
 int /*<<< orphan*/  tcps_tlpresends ; 

__attribute__((used)) static inline void
bbr_do_send_accounting(struct tcpcb *tp, struct tcp_bbr *bbr, struct bbr_sendmap *rsm, int32_t len, int32_t error)
{
	if (error) {
		bbr_do_error_accounting(tp, bbr, rsm, len, error);
		return;
	}
	if ((tp->t_flags & TF_FORCEDATA) && len == 1) {
		/* Window probe */
		TCPSTAT_INC(tcps_sndprobe);
#ifdef NETFLIX_STATS
		stats_voi_update_abs_u32(tp->t_stats,
		    VOI_TCP_RETXPB, len);
#endif
	} else if (rsm) {
		if (rsm->r_flags & BBR_TLP) {
			/*
			 * TLP should not count in retran count, but in its
			 * own bin
			 */
#ifdef NETFLIX_STATS
			tp->t_sndtlppack++;
			tp->t_sndtlpbyte += len;
			TCPSTAT_INC(tcps_tlpresends);
			TCPSTAT_ADD(tcps_tlpresend_bytes, len);
#endif
		} else {
			/* Retransmit */
			tp->t_sndrexmitpack++;
			TCPSTAT_INC(tcps_sndrexmitpack);
			TCPSTAT_ADD(tcps_sndrexmitbyte, len);
#ifdef NETFLIX_STATS
			stats_voi_update_abs_u32(tp->t_stats, VOI_TCP_RETXPB,
			    len);
#endif
		}
		/*
		 * Logs in 0 - 8, 8 is all non probe_bw states 0-7 is
		 * sub-state
		 */
		counter_u64_add(bbr_state_lost[rsm->r_bbr_state], len);
		if (bbr->rc_bbr_state != BBR_STATE_PROBE_BW) {
			/* Non probe_bw log in 1, 2, or 4. */
			counter_u64_add(bbr_state_resend[bbr->rc_bbr_state], len);
		} else {
			/*
			 * Log our probe state 3, and log also 5-13 to show
			 * us the recovery sub-state for the send. This
			 * means that 3 == (5+6+7+8+9+10+11+12+13)
			 */
			counter_u64_add(bbr_state_resend[BBR_STATE_PROBE_BW], len);
			counter_u64_add(bbr_state_resend[(bbr_state_val(bbr) + 5)], len);
		}
		/* Place in both 16's the totals of retransmitted */
		counter_u64_add(bbr_state_lost[16], len);
		counter_u64_add(bbr_state_resend[16], len);
		/* Place in 17's the total sent */
		counter_u64_add(bbr_state_resend[17], len);
		counter_u64_add(bbr_state_lost[17], len);

	} else {
		/* New sends */
		TCPSTAT_INC(tcps_sndpack);
		TCPSTAT_ADD(tcps_sndbyte, len);
		/* Place in 17's the total sent */
		counter_u64_add(bbr_state_resend[17], len);
		counter_u64_add(bbr_state_lost[17], len);
#ifdef NETFLIX_STATS
		stats_voi_update_abs_u64(tp->t_stats, VOI_TCP_TXPB,
		    len);
#endif
	}
}