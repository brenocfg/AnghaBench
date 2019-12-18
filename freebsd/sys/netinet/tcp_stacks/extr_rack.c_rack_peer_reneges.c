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
typedef  int /*<<< orphan*/  tcp_seq ;
struct TYPE_2__ {int /*<<< orphan*/  rack_sf; int /*<<< orphan*/  rc_mtree; int /*<<< orphan*/  rc_tmap; int /*<<< orphan*/  rc_sacked; } ;
struct tcp_rack {TYPE_1__ r_ctl; } ;
struct rack_sendmap {int r_flags; int r_in_tmap; scalar_t__ r_start; scalar_t__ r_end; } ;

/* Variables and functions */
 int RACK_ACKED ; 
 int RACK_SACK_PASSED ; 
 int RACK_WAS_SACKPASS ; 
 struct rack_sendmap* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rack_sendmap*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct rack_sendmap*,struct rack_sendmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct rack_sendmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,struct tcp_rack*,struct rack_sendmap*,int) ; 
 int /*<<< orphan*/  r_tnext ; 
 int /*<<< orphan*/  rack_rb_tree_head ; 
 scalar_t__ rack_use_sack_filter ; 
 int /*<<< orphan*/  sack_filter_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inline 
rack_peer_reneges(struct tcp_rack *rack, struct rack_sendmap *rsm, tcp_seq th_ack)
{
	struct rack_sendmap *tmap;

	tmap = NULL;
	while (rsm && (rsm->r_flags & RACK_ACKED)) {
		/* Its no longer sacked, mark it so */
		rack->r_ctl.rc_sacked -= (rsm->r_end - rsm->r_start);
#ifdef INVARIANTS
		if (rsm->r_in_tmap) {
			panic("rack:%p rsm:%p flags:0x%x in tmap?",
			      rack, rsm, rsm->r_flags);
		}
#endif
		rsm->r_flags &= ~(RACK_ACKED|RACK_SACK_PASSED|RACK_WAS_SACKPASS);
		/* Rebuild it into our tmap */
		if (tmap == NULL) {
			TAILQ_INSERT_HEAD(&rack->r_ctl.rc_tmap, rsm, r_tnext);
			tmap = rsm;
		} else {
			TAILQ_INSERT_AFTER(&rack->r_ctl.rc_tmap, tmap, rsm, r_tnext);
			tmap = rsm;
		}
		tmap->r_in_tmap = 1;
		rsm = RB_NEXT(rack_rb_tree_head, &rack->r_ctl.rc_mtree, rsm);
	}
	/* 
	 * Now lets possibly clear the sack filter so we start 
	 * recognizing sacks that cover this area.
	 */
	if (rack_use_sack_filter)
		sack_filter_clear(&rack->r_ctl.rack_sf, th_ack);

}