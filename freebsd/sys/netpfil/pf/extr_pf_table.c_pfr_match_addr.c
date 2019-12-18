#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in6 {int sin_len; int sin_family; int sin6_len; int sin6_family; int /*<<< orphan*/  sin6_addr; TYPE_1__ sin_addr; } ;
struct sockaddr_in {int sin_len; int sin_family; int sin6_len; int sin6_family; int /*<<< orphan*/  sin6_addr; TYPE_1__ sin_addr; } ;
struct pfr_ktable {int pfrkt_flags; int /*<<< orphan*/  pfrkt_nomatch; int /*<<< orphan*/  pfrkt_match; TYPE_3__* pfrkt_ip6; TYPE_2__* pfrkt_ip4; struct pfr_ktable* pfrkt_root; } ;
struct pfr_kentry {int /*<<< orphan*/  pfrke_not; } ;
struct pf_addr {int /*<<< orphan*/ * addr32; } ;
typedef  int /*<<< orphan*/  sin6 ;
typedef  int /*<<< orphan*/  sin ;
typedef  int sa_family_t ;
struct TYPE_6__ {int /*<<< orphan*/  rh; } ;
struct TYPE_5__ {int /*<<< orphan*/  rh; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  KENTRY_RNF_ROOT (struct pfr_kentry*) ; 
 int PFR_TFLAG_ACTIVE ; 
 int /*<<< orphan*/  PF_RULES_RASSERT () ; 
 int /*<<< orphan*/  bcopy (struct pf_addr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 scalar_t__ rn_match (struct sockaddr_in6*,int /*<<< orphan*/ *) ; 

int
pfr_match_addr(struct pfr_ktable *kt, struct pf_addr *a, sa_family_t af)
{
	struct pfr_kentry	*ke = NULL;
	int			 match;

	PF_RULES_RASSERT();

	if (!(kt->pfrkt_flags & PFR_TFLAG_ACTIVE) && kt->pfrkt_root != NULL)
		kt = kt->pfrkt_root;
	if (!(kt->pfrkt_flags & PFR_TFLAG_ACTIVE))
		return (0);

	switch (af) {
#ifdef INET
	case AF_INET:
	    {
		struct sockaddr_in sin;

		bzero(&sin, sizeof(sin));
		sin.sin_len = sizeof(sin);
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = a->addr32[0];
		ke = (struct pfr_kentry *)rn_match(&sin, &kt->pfrkt_ip4->rh);
		if (ke && KENTRY_RNF_ROOT(ke))
			ke = NULL;
		break;
	    }
#endif /* INET */
#ifdef INET6
	case AF_INET6:
	    {
		struct sockaddr_in6 sin6;

		bzero(&sin6, sizeof(sin6));
		sin6.sin6_len = sizeof(sin6);
		sin6.sin6_family = AF_INET6;
		bcopy(a, &sin6.sin6_addr, sizeof(sin6.sin6_addr));
		ke = (struct pfr_kentry *)rn_match(&sin6, &kt->pfrkt_ip6->rh);
		if (ke && KENTRY_RNF_ROOT(ke))
			ke = NULL;
		break;
	    }
#endif /* INET6 */
	}
	match = (ke && !ke->pfrke_not);
	if (match)
		counter_u64_add(kt->pfrkt_match, 1);
	else
		counter_u64_add(kt->pfrkt_nomatch, 1);
	return (match);
}