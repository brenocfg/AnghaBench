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
struct pfr_ktable {long pfrkt_tzero; int /*<<< orphan*/  pfrkt_nomatch; int /*<<< orphan*/  pfrkt_match; int /*<<< orphan*/ ** pfrkt_bytes; int /*<<< orphan*/ ** pfrkt_packets; } ;
struct pfr_kentryworkq {int dummy; } ;

/* Variables and functions */
 int PFR_DIR_MAX ; 
 int PFR_OP_TABLE_MAX ; 
 int /*<<< orphan*/  counter_u64_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfr_clstats_kentries (struct pfr_kentryworkq*,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfr_enqueue_addrs (struct pfr_ktable*,struct pfr_kentryworkq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pfr_clstats_ktable(struct pfr_ktable *kt, long tzero, int recurse)
{
	struct pfr_kentryworkq	 addrq;
	int			 pfr_dir, pfr_op;

	if (recurse) {
		pfr_enqueue_addrs(kt, &addrq, NULL, 0);
		pfr_clstats_kentries(&addrq, tzero, 0);
	}
	for (pfr_dir = 0; pfr_dir < PFR_DIR_MAX; pfr_dir ++) {
		for (pfr_op = 0; pfr_op < PFR_OP_TABLE_MAX; pfr_op ++) {
			counter_u64_zero(kt->pfrkt_packets[pfr_dir][pfr_op]);
			counter_u64_zero(kt->pfrkt_bytes[pfr_dir][pfr_op]);
		}
	}
	counter_u64_zero(kt->pfrkt_match);
	counter_u64_zero(kt->pfrkt_nomatch);
	kt->pfrkt_tzero = tzero;
}