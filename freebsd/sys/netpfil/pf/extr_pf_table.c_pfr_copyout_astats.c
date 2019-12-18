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
struct pfr_walktree {int pfrw_flags; } ;
struct pfr_kcounters {int /*<<< orphan*/ ** pfrkc_bytes; int /*<<< orphan*/ ** pfrkc_packets; int /*<<< orphan*/  pfrkc_tzero; } ;
struct pfr_kentry {struct pfr_kcounters pfrke_counters; } ;
struct TYPE_2__ {int /*<<< orphan*/  pfra_fback; } ;
struct pfr_astats {void*** pfras_bytes; void*** pfras_packets; TYPE_1__ pfras_a; int /*<<< orphan*/  pfras_tzero; } ;

/* Variables and functions */
 int PFR_DIR_MAX ; 
 int /*<<< orphan*/  PFR_FB_NOCOUNT ; 
 int PFR_OP_ADDR_MAX ; 
 int PFR_TFLAG_COUNTERS ; 
 int /*<<< orphan*/  bzero (void***,int) ; 
 void* counter_u64_fetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfr_copyout_addr (TYPE_1__*,struct pfr_kentry const*) ; 

__attribute__((used)) static void
pfr_copyout_astats(struct pfr_astats *as, const struct pfr_kentry *ke,
    const struct pfr_walktree *w)
{
	int dir, op;
	const struct pfr_kcounters *kc = &ke->pfrke_counters;

	pfr_copyout_addr(&as->pfras_a, ke);
	as->pfras_tzero = kc->pfrkc_tzero;

	if (! (w->pfrw_flags & PFR_TFLAG_COUNTERS)) {
		bzero(as->pfras_packets, sizeof(as->pfras_packets));
		bzero(as->pfras_bytes, sizeof(as->pfras_bytes));
		as->pfras_a.pfra_fback = PFR_FB_NOCOUNT;
		return;
	}

	for (dir = 0; dir < PFR_DIR_MAX; dir ++) {
		for (op = 0; op < PFR_OP_ADDR_MAX; op ++) {
			as->pfras_packets[dir][op] =
			    counter_u64_fetch(kc->pfrkc_packets[dir][op]);
			as->pfras_bytes[dir][op] =
			    counter_u64_fetch(kc->pfrkc_bytes[dir][op]);
		}
	}
}