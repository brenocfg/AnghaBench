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
struct pfr_walktree {int pfrw_cnt; struct pfr_kentry* pfrw_kentry; int /*<<< orphan*/  pfrw_op; } ;
struct pfr_ktable {TYPE_1__* pfrkt_ip6; TYPE_2__* pfrkt_ip4; } ;
struct pfr_kentry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rh; int /*<<< orphan*/  (* rnh_walktree ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pfr_walktree*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  rh; int /*<<< orphan*/  (* rnh_walktree ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pfr_walktree*) ;} ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  PFRW_POOL_GET ; 
 int /*<<< orphan*/  bzero (struct pfr_walktree*,int) ; 
 int /*<<< orphan*/  pfr_walktree ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pfr_walktree*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pfr_walktree*) ; 

__attribute__((used)) static struct pfr_kentry *
pfr_kentry_byidx(struct pfr_ktable *kt, int idx, int af)
{
	struct pfr_walktree	w;

	bzero(&w, sizeof(w));
	w.pfrw_op = PFRW_POOL_GET;
	w.pfrw_cnt = idx;

	switch (af) {
#ifdef INET
	case AF_INET:
		kt->pfrkt_ip4->rnh_walktree(&kt->pfrkt_ip4->rh, pfr_walktree, &w);
		return (w.pfrw_kentry);
#endif /* INET */
#ifdef INET6
	case AF_INET6:
		kt->pfrkt_ip6->rnh_walktree(&kt->pfrkt_ip6->rh, pfr_walktree, &w);
		return (w.pfrw_kentry);
#endif /* INET6 */
	default:
		return (NULL);
	}
}