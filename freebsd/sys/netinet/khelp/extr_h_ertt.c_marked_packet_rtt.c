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
typedef  void* uint32_t ;
struct txseginfo {void* tx_ts; int len; } ;
struct tcpcb {int t_flags; int /*<<< orphan*/  snd_cwnd; } ;
struct ertt {int /*<<< orphan*/  flags; int /*<<< orphan*/  marked_snd_cwnd; scalar_t__ bytes_tx_in_rtt; scalar_t__ bytes_tx_in_marked_rtt; void* markedpkt_rtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERTT_MEASUREMENT_IN_PROGRESS ; 
 int /*<<< orphan*/  ERTT_NEW_MEASUREMENT ; 
 int /*<<< orphan*/  ERTT_TSO_DISABLED ; 
 int FORCED_MEASUREMENT ; 
 int MULTI_ACK ; 
 int OLD_TXSI ; 
 int TF_TSO ; 
 void* tcp_ts_getticks () ; 

__attribute__((used)) static void inline
marked_packet_rtt(struct txseginfo *txsi, struct ertt *e_t, struct tcpcb *tp,
    uint32_t *pmeasurenext, int *pmeasurenext_len, int *prtt_bytes_adjust,
    int mflag)
{

	/*
	 * If we can't measure this one properly due to delayed acking adjust
	 * byte counters and flag to measure next txsi. Note that since the
	 * marked packet's transmitted bytes are measured we need to subtract the
	 * transmitted bytes. Then pretend the next txsi was marked.
	 */
	if (mflag & (MULTI_ACK|OLD_TXSI)) {
		*pmeasurenext = txsi->tx_ts;
		*pmeasurenext_len = txsi->len;
		*prtt_bytes_adjust += *pmeasurenext_len;
	} else {
		if (mflag & FORCED_MEASUREMENT) {
			e_t->markedpkt_rtt = tcp_ts_getticks() -
			    *pmeasurenext + 1;
			e_t->bytes_tx_in_marked_rtt = e_t->bytes_tx_in_rtt +
			    *pmeasurenext_len - *prtt_bytes_adjust;
		} else {
			e_t->markedpkt_rtt = tcp_ts_getticks() -
			    txsi->tx_ts + 1;
			e_t->bytes_tx_in_marked_rtt = e_t->bytes_tx_in_rtt -
			    *prtt_bytes_adjust;
		}
		e_t->marked_snd_cwnd = tp->snd_cwnd;

		/*
		 * Reset the ERTT_MEASUREMENT_IN_PROGRESS flag to indicate to
		 * add_tx_segment_info that a new measurement should be started.
		 */
		e_t->flags &= ~ERTT_MEASUREMENT_IN_PROGRESS;
		/*
		 * Set ERTT_NEW_MEASUREMENT to tell the congestion control
		 * algorithm that a new marked RTT measurement has has been made
		 * and is available for use.
		 */
		e_t->flags |= ERTT_NEW_MEASUREMENT;

		if (tp->t_flags & TF_TSO) {
			/* Temporarily disable TSO to aid a new measurment. */
			tp->t_flags &= ~TF_TSO;
			/* Keep track that we've disabled it. */
			e_t->flags |= ERTT_TSO_DISABLED;
		}
	}
}