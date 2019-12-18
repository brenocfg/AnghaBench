#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcphdr {int /*<<< orphan*/  th_ack; } ;
struct tcpcb {int snd_cwnd; scalar_t__ snd_ssthresh; int /*<<< orphan*/  t_flags; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  snd_recover; TYPE_2__* ccv; scalar_t__ t_fb_ptr; int /*<<< orphan*/  t_inpcb; } ;
struct TYPE_4__ {int rc_prop_rate; int rc_loss_count; scalar_t__ rc_prr_sndcnt; scalar_t__ rc_prop_reduce; } ;
struct tcp_rack {TYPE_1__ r_ctl; } ;
typedef  int int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* post_recovery ) (TYPE_2__*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  curack; } ;

/* Variables and functions */
 TYPE_3__* CC_ALGO (struct tcpcb*) ; 
 int /*<<< orphan*/  EXIT_RECOVERY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rack_log_to_prr (struct tcp_rack*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
rack_post_recovery(struct tcpcb *tp, struct tcphdr *th)
{
	struct tcp_rack *rack;

	INP_WLOCK_ASSERT(tp->t_inpcb);
	rack = (struct tcp_rack *)tp->t_fb_ptr;
	if (CC_ALGO(tp)->post_recovery != NULL) {
		tp->ccv->curack = th->th_ack;
		CC_ALGO(tp)->post_recovery(tp->ccv);
	}
	/*
	 * Here we can in theory adjust cwnd to be based on the number of
	 * losses in the window (rack->r_ctl.rc_loss_count). This is done
	 * based on the rack_use_proportional flag.
	 */
	if (rack->r_ctl.rc_prop_reduce && rack->r_ctl.rc_prop_rate) {
		int32_t reduce;

		reduce = (rack->r_ctl.rc_loss_count * rack->r_ctl.rc_prop_rate);
		if (reduce > 50) {
			reduce = 50;
		}
		tp->snd_cwnd -= ((reduce * tp->snd_cwnd) / 100);
	} else {
		if (tp->snd_cwnd > tp->snd_ssthresh) {
			/* Drop us down to the ssthresh (1/2 cwnd at loss) */
			tp->snd_cwnd = tp->snd_ssthresh;
		}
	}
	if (rack->r_ctl.rc_prr_sndcnt > 0) {
		/* Suck the next prr cnt back into cwnd */
		tp->snd_cwnd += rack->r_ctl.rc_prr_sndcnt;
		rack->r_ctl.rc_prr_sndcnt = 0;
		rack_log_to_prr(rack, 1);
	}
	tp->snd_recover = tp->snd_una;
	EXIT_RECOVERY(tp->t_flags);


}