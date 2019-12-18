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
struct TYPE_2__ {int /*<<< orphan*/  rc_map; int /*<<< orphan*/  rc_lost_bytes; int /*<<< orphan*/  rc_tmap; } ;
struct tcp_bbr {TYPE_1__ r_ctl; } ;
struct bbr_sendmap {scalar_t__ r_dupack; int r_flags; scalar_t__ r_limit_type; scalar_t__ r_start; scalar_t__ r_end; scalar_t__ r_app_limited; scalar_t__ r_in_tmap; scalar_t__ r_rtr_bytes; } ;

/* Variables and functions */
 int BBR_HAS_FIN ; 
 int BBR_MARKED_LOST ; 
 int BBR_RWND_COLLAPSED ; 
 int BBR_TLP ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct bbr_sendmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bbr_free (struct tcp_bbr*,struct bbr_sendmap*) ; 
 int /*<<< orphan*/  r_next ; 
 int /*<<< orphan*/  r_tnext ; 

__attribute__((used)) static struct bbr_sendmap *
bbr_merge_rsm(struct tcp_bbr *bbr,
	      struct bbr_sendmap *l_rsm,
	      struct bbr_sendmap *r_rsm)
{
	/* 
	 * We are merging two ack'd RSM's,
	 * the l_rsm is on the left (lower seq
	 * values) and the r_rsm is on the right
	 * (higher seq value). The simplest way
	 * to merge these is to move the right
	 * one into the left. I don't think there
	 * is any reason we need to try to find
	 * the oldest (or last oldest retransmitted).
	 */
	l_rsm->r_end = r_rsm->r_end;
	if (l_rsm->r_dupack < r_rsm->r_dupack)
		l_rsm->r_dupack = r_rsm->r_dupack;
	if (r_rsm->r_rtr_bytes)
		l_rsm->r_rtr_bytes += r_rsm->r_rtr_bytes;
	if (r_rsm->r_in_tmap) {
		/* This really should not happen */
		TAILQ_REMOVE(&bbr->r_ctl.rc_tmap, r_rsm, r_tnext);
	}
	if (r_rsm->r_app_limited)
		l_rsm->r_app_limited = r_rsm->r_app_limited;
	/* Now the flags */
	if (r_rsm->r_flags & BBR_HAS_FIN)
		l_rsm->r_flags |= BBR_HAS_FIN;
	if (r_rsm->r_flags & BBR_TLP)
		l_rsm->r_flags |= BBR_TLP;
	if (r_rsm->r_flags & BBR_RWND_COLLAPSED)
		l_rsm->r_flags |= BBR_RWND_COLLAPSED;
	if (r_rsm->r_flags & BBR_MARKED_LOST) {
		/* This really should not happen */
		bbr->r_ctl.rc_lost_bytes -= r_rsm->r_end - r_rsm->r_start;
	}
	TAILQ_REMOVE(&bbr->r_ctl.rc_map, r_rsm, r_next);	
	if ((r_rsm->r_limit_type == 0) && (l_rsm->r_limit_type != 0)) {
		/* Transfer the split limit to the map we free */
		r_rsm->r_limit_type = l_rsm->r_limit_type;
		l_rsm->r_limit_type = 0;
	}
	bbr_free(bbr, r_rsm);
	return(l_rsm);
}