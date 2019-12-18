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
struct pfr_walktree {struct pfi_dynaddr* pfrw_dyn; int /*<<< orphan*/  pfrw_op; } ;
struct pfr_ktable {TYPE_2__* pfrkt_ip6; TYPE_1__* pfrkt_ip4; } ;
struct pfi_dynaddr {scalar_t__ pfid_af; scalar_t__ pfid_acnt6; scalar_t__ pfid_acnt4; } ;
struct TYPE_4__ {int /*<<< orphan*/  rh; int /*<<< orphan*/  (* rnh_walktree ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pfr_walktree*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  rh; int /*<<< orphan*/  (* rnh_walktree ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pfr_walktree*) ;} ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  PFRW_DYNADDR_UPDATE ; 
 int /*<<< orphan*/  bzero (struct pfr_walktree*,int) ; 
 int /*<<< orphan*/  pfr_walktree ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pfr_walktree*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pfr_walktree*) ; 

void
pfr_dynaddr_update(struct pfr_ktable *kt, struct pfi_dynaddr *dyn)
{
	struct pfr_walktree	w;

	bzero(&w, sizeof(w));
	w.pfrw_op = PFRW_DYNADDR_UPDATE;
	w.pfrw_dyn = dyn;

	dyn->pfid_acnt4 = 0;
	dyn->pfid_acnt6 = 0;
	if (!dyn->pfid_af || dyn->pfid_af == AF_INET)
		kt->pfrkt_ip4->rnh_walktree(&kt->pfrkt_ip4->rh, pfr_walktree, &w);
	if (!dyn->pfid_af || dyn->pfid_af == AF_INET6)
		kt->pfrkt_ip6->rnh_walktree(&kt->pfrkt_ip6->rh, pfr_walktree, &w);
}