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
struct TYPE_2__ {int /*<<< orphan*/  rc_mtree; int /*<<< orphan*/  rc_tmap; } ;
struct tcp_rack {TYPE_1__ r_ctl; } ;
struct rack_sendmap {scalar_t__ r_dupack; int r_flags; scalar_t__ r_limit_type; scalar_t__ r_in_tmap; scalar_t__ r_rtr_bytes; int /*<<< orphan*/  r_end; } ;

/* Variables and functions */
 int RACK_HAS_FIN ; 
 int RACK_RWND_COLLAPSED ; 
 int RACK_TLP ; 
 struct rack_sendmap* RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rack_sendmap*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct rack_sendmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,struct tcp_rack*,struct rack_sendmap*,struct rack_sendmap*) ; 
 int /*<<< orphan*/  r_tnext ; 
 int /*<<< orphan*/  rack_free (struct tcp_rack*,struct rack_sendmap*) ; 
 int /*<<< orphan*/  rack_rb_tree_head ; 

__attribute__((used)) static struct rack_sendmap *
rack_merge_rsm(struct tcp_rack *rack,
	       struct rack_sendmap *l_rsm,
	       struct rack_sendmap *r_rsm)
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
	struct rack_sendmap *rm;
	
	l_rsm->r_end = r_rsm->r_end;
	if (l_rsm->r_dupack < r_rsm->r_dupack)
		l_rsm->r_dupack = r_rsm->r_dupack;
	if (r_rsm->r_rtr_bytes)
		l_rsm->r_rtr_bytes += r_rsm->r_rtr_bytes;
	if (r_rsm->r_in_tmap) {
		/* This really should not happen */
		TAILQ_REMOVE(&rack->r_ctl.rc_tmap, r_rsm, r_tnext);
		r_rsm->r_in_tmap = 0;
	}
	/* Now the flags */
	if (r_rsm->r_flags & RACK_HAS_FIN)
		l_rsm->r_flags |= RACK_HAS_FIN;
	if (r_rsm->r_flags & RACK_TLP)
		l_rsm->r_flags |= RACK_TLP;
	if (r_rsm->r_flags & RACK_RWND_COLLAPSED)
		l_rsm->r_flags |= RACK_RWND_COLLAPSED;
	rm = RB_REMOVE(rack_rb_tree_head, &rack->r_ctl.rc_mtree, r_rsm);
#ifdef INVARIANTS
	if (rm != r_rsm) {
		panic("removing head in rack:%p rsm:%p rm:%p",
		      rack, r_rsm, rm);
	}
#endif
	if ((r_rsm->r_limit_type == 0) && (l_rsm->r_limit_type != 0)) {
		/* Transfer the split limit to the map we free */
		r_rsm->r_limit_type = l_rsm->r_limit_type;
		l_rsm->r_limit_type = 0;
	}
	rack_free(rack, r_rsm);
	return(l_rsm);
}