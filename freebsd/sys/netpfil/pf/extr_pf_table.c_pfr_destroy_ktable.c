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
struct pfr_ktable {int /*<<< orphan*/  pfrkt_nomatch; int /*<<< orphan*/  pfrkt_match; int /*<<< orphan*/ ** pfrkt_bytes; int /*<<< orphan*/ ** pfrkt_packets; TYPE_1__* pfrkt_rs; struct pfr_ktable* pfrkt_shadow; int /*<<< orphan*/ * pfrkt_ip6; int /*<<< orphan*/ * pfrkt_ip4; } ;
struct pfr_kentryworkq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tables; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PFTABLE ; 
 int PFR_DIR_MAX ; 
 int PFR_OP_TABLE_MAX ; 
 int /*<<< orphan*/  counter_u64_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct pfr_ktable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_remove_if_empty_ruleset (TYPE_1__*) ; 
 int /*<<< orphan*/  pfr_clean_node_mask (struct pfr_ktable*,struct pfr_kentryworkq*) ; 
 int /*<<< orphan*/  pfr_destroy_kentries (struct pfr_kentryworkq*) ; 
 int /*<<< orphan*/  pfr_enqueue_addrs (struct pfr_ktable*,struct pfr_kentryworkq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rn_detachhead (void**) ; 

__attribute__((used)) static void
pfr_destroy_ktable(struct pfr_ktable *kt, int flushaddr)
{
	struct pfr_kentryworkq	 addrq;
	int			 pfr_dir, pfr_op;

	if (flushaddr) {
		pfr_enqueue_addrs(kt, &addrq, NULL, 0);
		pfr_clean_node_mask(kt, &addrq);
		pfr_destroy_kentries(&addrq);
	}
	if (kt->pfrkt_ip4 != NULL)
		rn_detachhead((void **)&kt->pfrkt_ip4);
	if (kt->pfrkt_ip6 != NULL)
		rn_detachhead((void **)&kt->pfrkt_ip6);
	if (kt->pfrkt_shadow != NULL)
		pfr_destroy_ktable(kt->pfrkt_shadow, flushaddr);
	if (kt->pfrkt_rs != NULL) {
		kt->pfrkt_rs->tables--;
		pf_remove_if_empty_ruleset(kt->pfrkt_rs);
	}
	for (pfr_dir = 0; pfr_dir < PFR_DIR_MAX; pfr_dir ++) {
		for (pfr_op = 0; pfr_op < PFR_OP_TABLE_MAX; pfr_op ++) {
			counter_u64_free(kt->pfrkt_packets[pfr_dir][pfr_op]);
			counter_u64_free(kt->pfrkt_bytes[pfr_dir][pfr_op]);
		}
	}
	counter_u64_free(kt->pfrkt_match);
	counter_u64_free(kt->pfrkt_nomatch);

	free(kt, M_PFTABLE);
}