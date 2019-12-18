#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sin6_len; int sin6_family; } ;
struct TYPE_5__ {int sin_len; int sin_family; } ;
union sockaddr_union {TYPE_2__ sin6; TYPE_1__ sin; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct pfr_ktable {int pfrkt_flags; int /*<<< orphan*/  pfrkt_match; TYPE_4__* pfrkt_ip6; TYPE_3__* pfrkt_ip4; int /*<<< orphan*/  pfrkt_nomatch; struct pfr_ktable* pfrkt_root; } ;
struct pfr_kentry {int /*<<< orphan*/  pfrke_net; union sockaddr_union pfrke_sa; } ;
struct pf_addr {int dummy; } ;
typedef  int const sa_family_t ;
struct TYPE_8__ {int /*<<< orphan*/  rh; } ;
struct TYPE_7__ {int /*<<< orphan*/  rh; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  KENTRY_NETWORK (struct pfr_kentry*) ; 
 int PFR_TFLAG_ACTIVE ; 
 int /*<<< orphan*/  PF_ACPY (struct pf_addr*,struct pf_addr*,int const) ; 
 int /*<<< orphan*/  PF_AINC (struct pf_addr*,int const) ; 
 int /*<<< orphan*/  PF_MATCHA (int /*<<< orphan*/ ,struct pf_addr*,struct pf_addr*,struct pf_addr*,int const) ; 
 int /*<<< orphan*/  PF_POOLMASK (struct pf_addr*,struct pf_addr*,struct pf_addr*,int /*<<< orphan*/ *,int const) ; 
 struct pf_addr* SUNION2PF (union sockaddr_union*,int const) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfr_ffaddr ; 
 struct pfr_kentry* pfr_kentry_byidx (struct pfr_ktable*,int,int const) ; 
 int /*<<< orphan*/  pfr_prepare_network (union sockaddr_union*,int const,int /*<<< orphan*/ ) ; 
 scalar_t__ rn_match (union sockaddr_union*,int /*<<< orphan*/ *) ; 

int
pfr_pool_get(struct pfr_ktable *kt, int *pidx, struct pf_addr *counter,
    sa_family_t af)
{
	struct pf_addr		 *addr, *cur, *mask;
	union sockaddr_union	 uaddr, umask;
	struct pfr_kentry	*ke, *ke2 = NULL;
	int			 idx = -1, use_counter = 0;

	switch (af) {
	case AF_INET:
		uaddr.sin.sin_len = sizeof(struct sockaddr_in);
		uaddr.sin.sin_family = AF_INET;
		break;
	case AF_INET6:
		uaddr.sin6.sin6_len = sizeof(struct sockaddr_in6);
		uaddr.sin6.sin6_family = AF_INET6;
		break;
	}
	addr = SUNION2PF(&uaddr, af);

	if (!(kt->pfrkt_flags & PFR_TFLAG_ACTIVE) && kt->pfrkt_root != NULL)
		kt = kt->pfrkt_root;
	if (!(kt->pfrkt_flags & PFR_TFLAG_ACTIVE))
		return (-1);

	if (pidx != NULL)
		idx = *pidx;
	if (counter != NULL && idx >= 0)
		use_counter = 1;
	if (idx < 0)
		idx = 0;

_next_block:
	ke = pfr_kentry_byidx(kt, idx, af);
	if (ke == NULL) {
		counter_u64_add(kt->pfrkt_nomatch, 1);
		return (1);
	}
	pfr_prepare_network(&umask, af, ke->pfrke_net);
	cur = SUNION2PF(&ke->pfrke_sa, af);
	mask = SUNION2PF(&umask, af);

	if (use_counter) {
		/* is supplied address within block? */
		if (!PF_MATCHA(0, cur, mask, counter, af)) {
			/* no, go to next block in table */
			idx++;
			use_counter = 0;
			goto _next_block;
		}
		PF_ACPY(addr, counter, af);
	} else {
		/* use first address of block */
		PF_ACPY(addr, cur, af);
	}

	if (!KENTRY_NETWORK(ke)) {
		/* this is a single IP address - no possible nested block */
		PF_ACPY(counter, addr, af);
		*pidx = idx;
		counter_u64_add(kt->pfrkt_match, 1);
		return (0);
	}
	for (;;) {
		/* we don't want to use a nested block */
		switch (af) {
		case AF_INET:
			ke2 = (struct pfr_kentry *)rn_match(&uaddr,
			    &kt->pfrkt_ip4->rh);
			break;
		case AF_INET6:
			ke2 = (struct pfr_kentry *)rn_match(&uaddr,
			    &kt->pfrkt_ip6->rh);
			break;
		}
		/* no need to check KENTRY_RNF_ROOT() here */
		if (ke2 == ke) {
			/* lookup return the same block - perfect */
			PF_ACPY(counter, addr, af);
			*pidx = idx;
			counter_u64_add(kt->pfrkt_match, 1);
			return (0);
		}

		/* we need to increase the counter past the nested block */
		pfr_prepare_network(&umask, AF_INET, ke2->pfrke_net);
		PF_POOLMASK(addr, addr, SUNION2PF(&umask, af), &pfr_ffaddr, af);
		PF_AINC(addr, af);
		if (!PF_MATCHA(0, cur, mask, addr, af)) {
			/* ok, we reached the end of our main block */
			/* go to next block in table */
			idx++;
			use_counter = 0;
			goto _next_block;
		}
	}
}