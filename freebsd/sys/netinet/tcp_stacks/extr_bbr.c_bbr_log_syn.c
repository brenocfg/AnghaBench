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
typedef  int /*<<< orphan*/  uint32_t ;
struct tcpopt {int dummy; } ;
struct tcpcb {scalar_t__ t_fb_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  rc_map; struct bbr_sendmap* rc_next; int /*<<< orphan*/  rc_tmap; int /*<<< orphan*/  rc_holes_rxt; int /*<<< orphan*/  rc_rcvtime; } ;
struct tcp_bbr {TYPE_1__ r_ctl; } ;
struct bbr_sendmap {int r_flags; int r_end; int r_start; scalar_t__ r_in_tmap; scalar_t__ r_rtr_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_CUM_ACKED ; 
 int BBR_HAS_SYN ; 
 void* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct bbr_sendmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bbr_free (struct tcp_bbr*,struct bbr_sendmap*) ; 
 int /*<<< orphan*/  bbr_update_rtt (struct tcpcb*,struct tcp_bbr*,struct bbr_sendmap*,struct tcpopt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_next ; 
 int /*<<< orphan*/  r_tnext ; 

__attribute__((used)) static void
bbr_log_syn(struct tcpcb *tp, struct tcpopt *to)
{
	struct tcp_bbr *bbr;
	struct bbr_sendmap *rsm;
	uint32_t cts;
	
	bbr = (struct tcp_bbr *)tp->t_fb_ptr;
	cts = bbr->r_ctl.rc_rcvtime;
	rsm = TAILQ_FIRST(&bbr->r_ctl.rc_map);
	if (rsm && (rsm->r_flags & BBR_HAS_SYN)) {
		if ((rsm->r_end - rsm->r_start) <= 1) {
			/* Log out the SYN completely */
			bbr->r_ctl.rc_holes_rxt -= rsm->r_rtr_bytes;
			rsm->r_rtr_bytes = 0;
			TAILQ_REMOVE(&bbr->r_ctl.rc_map, rsm, r_next);
			if (rsm->r_in_tmap) {
				TAILQ_REMOVE(&bbr->r_ctl.rc_tmap, rsm, r_tnext);
				rsm->r_in_tmap = 0;
			}
			if (bbr->r_ctl.rc_next == rsm) {
				/* scoot along the marker */
				bbr->r_ctl.rc_next = TAILQ_FIRST(&bbr->r_ctl.rc_map);
			}
			if (to != NULL)
				bbr_update_rtt(tp, bbr, rsm, to, cts, BBR_CUM_ACKED, 0);
			bbr_free(bbr, rsm);
		} else {
			/* There is more (Fast open)? strip out SYN. */
			rsm->r_flags &= ~BBR_HAS_SYN;
			rsm->r_start++;
		}
	}
}