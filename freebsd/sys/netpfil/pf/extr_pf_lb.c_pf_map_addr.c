#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pf_addr {int* addr32; } ;
struct pf_src_node {struct pf_addr raddr; } ;
struct pf_pool {int opts; int tblidx; struct pf_addr counter; struct pf_pooladdr* cur; int /*<<< orphan*/  list; int /*<<< orphan*/  key; } ;
struct pf_rule {struct pf_pool rpool; } ;
struct TYPE_7__ {struct pf_addr mask; struct pf_addr addr; } ;
struct TYPE_8__ {TYPE_1__ a; } ;
struct TYPE_10__ {TYPE_3__* dyn; int /*<<< orphan*/  tbl; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_2__ v; TYPE_4__ p; } ;
struct pf_pooladdr {TYPE_5__ addr; } ;
typedef  int sa_family_t ;
struct TYPE_12__ {scalar_t__ debug; } ;
struct TYPE_9__ {int pfid_acnt4; int pfid_acnt6; int /*<<< orphan*/  pfid_kt; struct pf_addr pfid_mask6; struct pf_addr pfid_addr6; struct pf_addr pfid_mask4; struct pf_addr pfid_addr4; } ;

/* Variables and functions */
#define  AF_INET 134 
#define  AF_INET6 133 
 int /*<<< orphan*/  PF_ACPY (struct pf_addr*,struct pf_addr*,int) ; 
 scalar_t__ PF_ADDR_DYNIFTL ; 
 scalar_t__ PF_ADDR_NOROUTE ; 
 scalar_t__ PF_ADDR_TABLE ; 
 scalar_t__ PF_AEQ (struct pf_addr*,struct pf_addr*,int) ; 
 int /*<<< orphan*/  PF_AINC (struct pf_addr*,int) ; 
 scalar_t__ PF_AZERO (struct pf_addr*,int) ; 
 scalar_t__ PF_DEBUG_MISC ; 
 int /*<<< orphan*/  PF_POOLMASK (struct pf_addr*,struct pf_addr*,struct pf_addr*,struct pf_addr*,int) ; 
#define  PF_POOL_BITMASK 132 
#define  PF_POOL_NONE 131 
#define  PF_POOL_RANDOM 130 
#define  PF_POOL_ROUNDROBIN 129 
#define  PF_POOL_SRCHASH 128 
 int PF_POOL_STICKYADDR ; 
 int PF_POOL_TYPEMASK ; 
 struct pf_pooladdr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct pf_pooladdr* TAILQ_NEXT (struct pf_pooladdr*,int /*<<< orphan*/ ) ; 
 TYPE_6__ V_pf_status ; 
 int /*<<< orphan*/  arc4random () ; 
 int /*<<< orphan*/  entries ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 struct pf_src_node* pf_find_src_node (struct pf_addr*,struct pf_rule*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_hash (struct pf_addr*,struct pf_addr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pf_match_addr (int /*<<< orphan*/ ,struct pf_addr*,struct pf_addr*,struct pf_addr*,int) ; 
 int /*<<< orphan*/  pf_print_host (struct pf_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfr_pool_get (int /*<<< orphan*/ ,int*,struct pf_addr*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
pf_map_addr(sa_family_t af, struct pf_rule *r, struct pf_addr *saddr,
    struct pf_addr *naddr, struct pf_addr *init_addr, struct pf_src_node **sn)
{
	struct pf_pool		*rpool = &r->rpool;
	struct pf_addr		*raddr = NULL, *rmask = NULL;

	/* Try to find a src_node if none was given and this
	   is a sticky-address rule. */
	if (*sn == NULL && r->rpool.opts & PF_POOL_STICKYADDR &&
	    (r->rpool.opts & PF_POOL_TYPEMASK) != PF_POOL_NONE)
		*sn = pf_find_src_node(saddr, r, af, 0);

	/* If a src_node was found or explicitly given and it has a non-zero
	   route address, use this address. A zeroed address is found if the
	   src node was created just a moment ago in pf_create_state and it
	   needs to be filled in with routing decision calculated here. */
	if (*sn != NULL && !PF_AZERO(&(*sn)->raddr, af)) {
		/* If the supplied address is the same as the current one we've
		 * been asked before, so tell the caller that there's no other
		 * address to be had. */
		if (PF_AEQ(naddr, &(*sn)->raddr, af))
			return (1);

		PF_ACPY(naddr, &(*sn)->raddr, af);
		if (V_pf_status.debug >= PF_DEBUG_MISC) {
			printf("pf_map_addr: src tracking maps ");
			pf_print_host(saddr, 0, af);
			printf(" to ");
			pf_print_host(naddr, 0, af);
			printf("\n");
		}
		return (0);
	}

	/* Find the route using chosen algorithm. Store the found route
	   in src_node if it was given or found. */
	if (rpool->cur->addr.type == PF_ADDR_NOROUTE)
		return (1);
	if (rpool->cur->addr.type == PF_ADDR_DYNIFTL) {
		switch (af) {
#ifdef INET
		case AF_INET:
			if (rpool->cur->addr.p.dyn->pfid_acnt4 < 1 &&
			    (rpool->opts & PF_POOL_TYPEMASK) !=
			    PF_POOL_ROUNDROBIN)
				return (1);
			 raddr = &rpool->cur->addr.p.dyn->pfid_addr4;
			 rmask = &rpool->cur->addr.p.dyn->pfid_mask4;
			break;
#endif /* INET */
#ifdef INET6
		case AF_INET6:
			if (rpool->cur->addr.p.dyn->pfid_acnt6 < 1 &&
			    (rpool->opts & PF_POOL_TYPEMASK) !=
			    PF_POOL_ROUNDROBIN)
				return (1);
			raddr = &rpool->cur->addr.p.dyn->pfid_addr6;
			rmask = &rpool->cur->addr.p.dyn->pfid_mask6;
			break;
#endif /* INET6 */
		}
	} else if (rpool->cur->addr.type == PF_ADDR_TABLE) {
		if ((rpool->opts & PF_POOL_TYPEMASK) != PF_POOL_ROUNDROBIN)
			return (1); /* unsupported */
	} else {
		raddr = &rpool->cur->addr.v.a.addr;
		rmask = &rpool->cur->addr.v.a.mask;
	}

	switch (rpool->opts & PF_POOL_TYPEMASK) {
	case PF_POOL_NONE:
		PF_ACPY(naddr, raddr, af);
		break;
	case PF_POOL_BITMASK:
		PF_POOLMASK(naddr, raddr, rmask, saddr, af);
		break;
	case PF_POOL_RANDOM:
		if (init_addr != NULL && PF_AZERO(init_addr, af)) {
			switch (af) {
#ifdef INET
			case AF_INET:
				rpool->counter.addr32[0] = htonl(arc4random());
				break;
#endif /* INET */
#ifdef INET6
			case AF_INET6:
				if (rmask->addr32[3] != 0xffffffff)
					rpool->counter.addr32[3] =
					    htonl(arc4random());
				else
					break;
				if (rmask->addr32[2] != 0xffffffff)
					rpool->counter.addr32[2] =
					    htonl(arc4random());
				else
					break;
				if (rmask->addr32[1] != 0xffffffff)
					rpool->counter.addr32[1] =
					    htonl(arc4random());
				else
					break;
				if (rmask->addr32[0] != 0xffffffff)
					rpool->counter.addr32[0] =
					    htonl(arc4random());
				break;
#endif /* INET6 */
			}
			PF_POOLMASK(naddr, raddr, rmask, &rpool->counter, af);
			PF_ACPY(init_addr, naddr, af);

		} else {
			PF_AINC(&rpool->counter, af);
			PF_POOLMASK(naddr, raddr, rmask, &rpool->counter, af);
		}
		break;
	case PF_POOL_SRCHASH:
	    {
		unsigned char hash[16];

		pf_hash(saddr, (struct pf_addr *)&hash, &rpool->key, af);
		PF_POOLMASK(naddr, raddr, rmask, (struct pf_addr *)&hash, af);
		break;
	    }
	case PF_POOL_ROUNDROBIN:
	    {
		struct pf_pooladdr *acur = rpool->cur;

		/*
		 * XXXGL: in the round-robin case we need to store
		 * the round-robin machine state in the rule, thus
		 * forwarding thread needs to modify rule.
		 *
		 * This is done w/o locking, because performance is assumed
		 * more important than round-robin precision.
		 *
		 * In the simpliest case we just update the "rpool->cur"
		 * pointer. However, if pool contains tables or dynamic
		 * addresses, then "tblidx" is also used to store machine
		 * state. Since "tblidx" is int, concurrent access to it can't
		 * lead to inconsistence, only to lost of precision.
		 *
		 * Things get worse, if table contains not hosts, but
		 * prefixes. In this case counter also stores machine state,
		 * and for IPv6 address, counter can't be updated atomically.
		 * Probably, using round-robin on a table containing IPv6
		 * prefixes (or even IPv4) would cause a panic.
		 */

		if (rpool->cur->addr.type == PF_ADDR_TABLE) {
			if (!pfr_pool_get(rpool->cur->addr.p.tbl,
			    &rpool->tblidx, &rpool->counter, af))
				goto get_addr;
		} else if (rpool->cur->addr.type == PF_ADDR_DYNIFTL) {
			if (!pfr_pool_get(rpool->cur->addr.p.dyn->pfid_kt,
			    &rpool->tblidx, &rpool->counter, af))
				goto get_addr;
		} else if (pf_match_addr(0, raddr, rmask, &rpool->counter, af))
			goto get_addr;

	try_next:
		if (TAILQ_NEXT(rpool->cur, entries) == NULL)
			rpool->cur = TAILQ_FIRST(&rpool->list);
		else
			rpool->cur = TAILQ_NEXT(rpool->cur, entries);
		if (rpool->cur->addr.type == PF_ADDR_TABLE) {
			rpool->tblidx = -1;
			if (pfr_pool_get(rpool->cur->addr.p.tbl,
			    &rpool->tblidx, &rpool->counter, af)) {
				/* table contains no address of type 'af' */
				if (rpool->cur != acur)
					goto try_next;
				return (1);
			}
		} else if (rpool->cur->addr.type == PF_ADDR_DYNIFTL) {
			rpool->tblidx = -1;
			if (pfr_pool_get(rpool->cur->addr.p.dyn->pfid_kt,
			    &rpool->tblidx, &rpool->counter, af)) {
				/* table contains no address of type 'af' */
				if (rpool->cur != acur)
					goto try_next;
				return (1);
			}
		} else {
			raddr = &rpool->cur->addr.v.a.addr;
			rmask = &rpool->cur->addr.v.a.mask;
			PF_ACPY(&rpool->counter, raddr, af);
		}

	get_addr:
		PF_ACPY(naddr, &rpool->counter, af);
		if (init_addr != NULL && PF_AZERO(init_addr, af))
			PF_ACPY(init_addr, naddr, af);
		PF_AINC(&rpool->counter, af);
		break;
	    }
	}
	if (*sn != NULL)
		PF_ACPY(&(*sn)->raddr, naddr, af);

	if (V_pf_status.debug >= PF_DEBUG_MISC &&
	    (rpool->opts & PF_POOL_TYPEMASK) != PF_POOL_NONE) {
		printf("pf_map_addr: selected address ");
		pf_print_host(naddr, 0, af);
		printf("\n");
	}

	return (0);
}