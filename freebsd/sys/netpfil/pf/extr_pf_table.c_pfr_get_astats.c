#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  w ;
struct pfr_walktree {int pfrw_free; int pfrw_flags; struct pfr_astats* pfrw_astats; int /*<<< orphan*/  pfrw_op; } ;
struct pfr_table {int dummy; } ;
struct pfr_ktable {int pfrkt_flags; int pfrkt_cnt; TYPE_2__* pfrkt_ip6; TYPE_1__* pfrkt_ip4; } ;
struct pfr_kentryworkq {int dummy; } ;
struct pfr_astats {int dummy; } ;
struct TYPE_4__ {int (* rnh_walktree ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pfr_walktree*) ;int /*<<< orphan*/  rh; } ;
struct TYPE_3__ {int (* rnh_walktree ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pfr_walktree*) ;int /*<<< orphan*/  rh; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEPT_FLAGS (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOTTY ; 
 int ESRCH ; 
 int /*<<< orphan*/  PFRW_GET_ASTATS ; 
 int PFR_FLAG_CLSTATS ; 
 int PFR_TFLAG_ACTIVE ; 
 int /*<<< orphan*/  PF_RULES_RASSERT () ; 
 int /*<<< orphan*/  bzero (struct pfr_walktree*,int) ; 
 int /*<<< orphan*/  pfr_clstats_kentries (struct pfr_kentryworkq*,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfr_enqueue_addrs (struct pfr_ktable*,struct pfr_kentryworkq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pfr_ktable* pfr_lookup_table (struct pfr_table*) ; 
 scalar_t__ pfr_validate_table (struct pfr_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfr_walktree ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pfr_walktree*) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pfr_walktree*) ; 
 long time_second ; 

int
pfr_get_astats(struct pfr_table *tbl, struct pfr_astats *addr, int *size,
	int flags)
{
	struct pfr_ktable	*kt;
	struct pfr_walktree	 w;
	struct pfr_kentryworkq	 workq;
	int			 rv;
	long			 tzero = time_second;

	PF_RULES_RASSERT();

	/* XXX PFR_FLAG_CLSTATS disabled */
	ACCEPT_FLAGS(flags, 0);
	if (pfr_validate_table(tbl, 0, 0))
		return (EINVAL);
	kt = pfr_lookup_table(tbl);
	if (kt == NULL || !(kt->pfrkt_flags & PFR_TFLAG_ACTIVE))
		return (ESRCH);
	if (kt->pfrkt_cnt > *size) {
		*size = kt->pfrkt_cnt;
		return (0);
	}

	bzero(&w, sizeof(w));
	w.pfrw_op = PFRW_GET_ASTATS;
	w.pfrw_astats = addr;
	w.pfrw_free = kt->pfrkt_cnt;
	/*
	 * Flags below are for backward compatibility. It was possible to have
	 * a table without per-entry counters. Now they are always allocated,
	 * we just discard data when reading it if table is not configured to
	 * have counters.
	 */
	w.pfrw_flags = kt->pfrkt_flags;
	rv = kt->pfrkt_ip4->rnh_walktree(&kt->pfrkt_ip4->rh, pfr_walktree, &w);
	if (!rv)
		rv = kt->pfrkt_ip6->rnh_walktree(&kt->pfrkt_ip6->rh,
		    pfr_walktree, &w);
	if (!rv && (flags & PFR_FLAG_CLSTATS)) {
		pfr_enqueue_addrs(kt, &workq, NULL, 0);
		pfr_clstats_kentries(&workq, tzero, 0);
	}
	if (rv)
		return (rv);

	if (w.pfrw_free) {
		printf("pfr_get_astats: corruption detected (%d).\n",
		    w.pfrw_free);
		return (ENOTTY);
	}
	*size = kt->pfrkt_cnt;
	return (0);
}