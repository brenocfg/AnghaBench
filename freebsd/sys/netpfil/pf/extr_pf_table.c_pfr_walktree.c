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
typedef  union sockaddr_union {int dummy; } sockaddr_union ;
struct radix_node {int dummy; } ;
struct pfr_walktree {int pfrw_op; TYPE_1__* pfrw_dyn; struct pfr_kentry* pfrw_kentry; int /*<<< orphan*/  pfrw_cnt; int /*<<< orphan*/  pfrw_astats; int /*<<< orphan*/  pfrw_free; int /*<<< orphan*/  pfrw_addr; int /*<<< orphan*/  pfrw_workq; } ;
struct pfr_kentry {union sockaddr_union pfrke_sa; int /*<<< orphan*/  pfrke_net; int /*<<< orphan*/  pfrke_af; int /*<<< orphan*/  pfrke_not; int /*<<< orphan*/  pfrke_mark; } ;
struct pfr_astats {int dummy; } ;
typedef  int /*<<< orphan*/  as ;
struct TYPE_2__ {void* pfid_mask6; void* pfid_addr6; int /*<<< orphan*/  pfid_acnt6; void* pfid_mask4; void* pfid_addr4; int /*<<< orphan*/  pfid_acnt4; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
#define  PFRW_DYNADDR_UPDATE 134 
#define  PFRW_ENQUEUE 133 
#define  PFRW_GET_ADDRS 132 
#define  PFRW_GET_ASTATS 131 
#define  PFRW_MARK 130 
#define  PFRW_POOL_GET 129 
#define  PFRW_SWEEP 128 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ ,struct pfr_kentry*,int /*<<< orphan*/ ) ; 
 void** SUNION2PF (union sockaddr_union*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct pfr_astats*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfr_copyout_addr (int /*<<< orphan*/ ,struct pfr_kentry*) ; 
 int /*<<< orphan*/  pfr_copyout_astats (struct pfr_astats*,struct pfr_kentry*,struct pfr_walktree*) ; 
 int /*<<< orphan*/  pfr_prepare_network (union sockaddr_union*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfrke_workq ; 

__attribute__((used)) static int
pfr_walktree(struct radix_node *rn, void *arg)
{
	struct pfr_kentry	*ke = (struct pfr_kentry *)rn;
	struct pfr_walktree	*w = arg;

	switch (w->pfrw_op) {
	case PFRW_MARK:
		ke->pfrke_mark = 0;
		break;
	case PFRW_SWEEP:
		if (ke->pfrke_mark)
			break;
		/* FALLTHROUGH */
	case PFRW_ENQUEUE:
		SLIST_INSERT_HEAD(w->pfrw_workq, ke, pfrke_workq);
		w->pfrw_cnt++;
		break;
	case PFRW_GET_ADDRS:
		if (w->pfrw_free-- > 0) {
			pfr_copyout_addr(w->pfrw_addr, ke);
			w->pfrw_addr++;
		}
		break;
	case PFRW_GET_ASTATS:
		if (w->pfrw_free-- > 0) {
			struct pfr_astats as;

			pfr_copyout_astats(&as, ke, w);

			bcopy(&as, w->pfrw_astats, sizeof(as));
			w->pfrw_astats++;
		}
		break;
	case PFRW_POOL_GET:
		if (ke->pfrke_not)
			break; /* negative entries are ignored */
		if (!w->pfrw_cnt--) {
			w->pfrw_kentry = ke;
			return (1); /* finish search */
		}
		break;
	case PFRW_DYNADDR_UPDATE:
	    {
		union sockaddr_union	pfr_mask;

		if (ke->pfrke_af == AF_INET) {
			if (w->pfrw_dyn->pfid_acnt4++ > 0)
				break;
			pfr_prepare_network(&pfr_mask, AF_INET, ke->pfrke_net);
			w->pfrw_dyn->pfid_addr4 = *SUNION2PF(&ke->pfrke_sa,
			    AF_INET);
			w->pfrw_dyn->pfid_mask4 = *SUNION2PF(&pfr_mask,
			    AF_INET);
		} else if (ke->pfrke_af == AF_INET6){
			if (w->pfrw_dyn->pfid_acnt6++ > 0)
				break;
			pfr_prepare_network(&pfr_mask, AF_INET6, ke->pfrke_net);
			w->pfrw_dyn->pfid_addr6 = *SUNION2PF(&ke->pfrke_sa,
			    AF_INET6);
			w->pfrw_dyn->pfid_mask6 = *SUNION2PF(&pfr_mask,
			    AF_INET6);
		}
		break;
	    }
	}
	return (0);
}