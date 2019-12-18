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
typedef  scalar_t__ uint32_t ;
struct tcpcb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rc_tmap; int /*<<< orphan*/  rc_map; } ;
struct tcp_bbr {TYPE_1__ r_ctl; } ;
struct bbr_sendmap {int r_in_tmap; int /*<<< orphan*/  r_flags; scalar_t__ r_dupack; scalar_t__ r_end; scalar_t__ r_start; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_HAS_FIN ; 
 scalar_t__ SEQ_GEQ (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct bbr_sendmap*,struct bbr_sendmap*,int /*<<< orphan*/ ) ; 
 struct bbr_sendmap* bbr_alloc_full_limit (struct tcp_bbr*) ; 
 int /*<<< orphan*/  bbr_clone_rsm (struct tcp_bbr*,struct bbr_sendmap*,struct bbr_sendmap*,scalar_t__) ; 
 int /*<<< orphan*/  bbr_update_rsm (struct tcpcb*,struct tcp_bbr*,struct bbr_sendmap*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  r_next ; 
 int /*<<< orphan*/  r_tnext ; 

__attribute__((used)) static uint32_t
bbr_update_entry(struct tcpcb *tp, struct tcp_bbr *bbr,
    struct bbr_sendmap *rsm, uint32_t cts, int32_t *lenp, uint32_t pacing_time)
{
	/*
	 * We (re-)transmitted starting at rsm->r_start for some length
	 * (possibly less than r_end.
	 */
	struct bbr_sendmap *nrsm;
	uint32_t c_end;
	int32_t len;

	len = *lenp;
	c_end = rsm->r_start + len;
	if (SEQ_GEQ(c_end, rsm->r_end)) {
		/*
		 * We retransmitted the whole piece or more than the whole
		 * slopping into the next rsm.
		 */
		bbr_update_rsm(tp, bbr, rsm, cts, pacing_time);
		if (c_end == rsm->r_end) {
			*lenp = 0;
			return (0);
		} else {
			int32_t act_len;

			/* Hangs over the end return whats left */
			act_len = rsm->r_end - rsm->r_start;
			*lenp = (len - act_len);
			return (rsm->r_end);
		}
		/* We don't get out of this block. */
	}
	/*
	 * Here we retransmitted less than the whole thing which means we
	 * have to split this into what was transmitted and what was not.
	 */
	nrsm = bbr_alloc_full_limit(bbr);
	if (nrsm == NULL) {
		*lenp = 0;
		return (0);
	}
	/*
	 * So here we are going to take the original rsm and make it what we
	 * retransmitted. nrsm will be the tail portion we did not
	 * retransmit. For example say the chunk was 1, 11 (10 bytes). And
	 * we retransmitted 5 bytes i.e. 1, 5. The original piece shrinks to
	 * 1, 6 and the new piece will be 6, 11.
	 */
	bbr_clone_rsm(bbr, nrsm, rsm, c_end);
	TAILQ_INSERT_AFTER(&bbr->r_ctl.rc_map, rsm, nrsm, r_next);
	nrsm->r_dupack = 0;
	if (rsm->r_in_tmap) {
		TAILQ_INSERT_AFTER(&bbr->r_ctl.rc_tmap, rsm, nrsm, r_tnext);
		nrsm->r_in_tmap = 1;
	}
	rsm->r_flags &= (~BBR_HAS_FIN);
	bbr_update_rsm(tp, bbr, rsm, cts, pacing_time);
	*lenp = 0;
	return (0);
}