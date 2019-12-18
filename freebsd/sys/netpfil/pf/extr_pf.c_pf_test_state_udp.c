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
struct udphdr {scalar_t__ uh_sport; scalar_t__ uh_dport; int /*<<< orphan*/  uh_sum; } ;
struct pfi_kif {int dummy; } ;
struct pf_state_peer {scalar_t__ state; } ;
struct pf_state_key_cmp {scalar_t__* port; int /*<<< orphan*/  af; int /*<<< orphan*/ * addr; int /*<<< orphan*/  proto; } ;
struct pf_state_key {scalar_t__* port; int /*<<< orphan*/ * addr; } ;
struct pf_state {int direction; struct pf_state_key** key; int /*<<< orphan*/  timeout; int /*<<< orphan*/  expire; struct pf_state_peer src; struct pf_state_peer dst; } ;
struct TYPE_2__ {struct udphdr* udp; } ;
struct pf_pdesc {size_t didx; size_t sidx; int /*<<< orphan*/  af; int /*<<< orphan*/  ip_sum; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ hdr; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  PFTM_UDP_MULTIPLE ; 
 int /*<<< orphan*/  PFTM_UDP_SINGLE ; 
 scalar_t__ PFUDPS_MULTIPLE ; 
 scalar_t__ PFUDPS_SINGLE ; 
 int /*<<< orphan*/  PF_ACPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PF_ANEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PF_IN ; 
 int PF_PASS ; 
 size_t PF_SK_STACK ; 
 size_t PF_SK_WIRE ; 
 int /*<<< orphan*/  STATE_LOOKUP (struct pfi_kif*,struct pf_state_key_cmp*,int,struct pf_state*,struct pf_pdesc*) ; 
 int /*<<< orphan*/  bzero (struct pf_state_key_cmp*,int) ; 
 int /*<<< orphan*/  m_copyback (struct mbuf*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_change_ap (struct mbuf*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_uptime ; 

__attribute__((used)) static int
pf_test_state_udp(struct pf_state **state, int direction, struct pfi_kif *kif,
    struct mbuf *m, int off, void *h, struct pf_pdesc *pd)
{
	struct pf_state_peer	*src, *dst;
	struct pf_state_key_cmp	 key;
	struct udphdr		*uh = pd->hdr.udp;

	bzero(&key, sizeof(key));
	key.af = pd->af;
	key.proto = IPPROTO_UDP;
	if (direction == PF_IN)	{	/* wire side, straight */
		PF_ACPY(&key.addr[0], pd->src, key.af);
		PF_ACPY(&key.addr[1], pd->dst, key.af);
		key.port[0] = uh->uh_sport;
		key.port[1] = uh->uh_dport;
	} else {			/* stack side, reverse */
		PF_ACPY(&key.addr[1], pd->src, key.af);
		PF_ACPY(&key.addr[0], pd->dst, key.af);
		key.port[1] = uh->uh_sport;
		key.port[0] = uh->uh_dport;
	}

	STATE_LOOKUP(kif, &key, direction, *state, pd);

	if (direction == (*state)->direction) {
		src = &(*state)->src;
		dst = &(*state)->dst;
	} else {
		src = &(*state)->dst;
		dst = &(*state)->src;
	}

	/* update states */
	if (src->state < PFUDPS_SINGLE)
		src->state = PFUDPS_SINGLE;
	if (dst->state == PFUDPS_SINGLE)
		dst->state = PFUDPS_MULTIPLE;

	/* update expire time */
	(*state)->expire = time_uptime;
	if (src->state == PFUDPS_MULTIPLE && dst->state == PFUDPS_MULTIPLE)
		(*state)->timeout = PFTM_UDP_MULTIPLE;
	else
		(*state)->timeout = PFTM_UDP_SINGLE;

	/* translate source/destination address, if necessary */
	if ((*state)->key[PF_SK_WIRE] != (*state)->key[PF_SK_STACK]) {
		struct pf_state_key *nk = (*state)->key[pd->didx];

		if (PF_ANEQ(pd->src, &nk->addr[pd->sidx], pd->af) ||
		    nk->port[pd->sidx] != uh->uh_sport)
			pf_change_ap(m, pd->src, &uh->uh_sport, pd->ip_sum,
			    &uh->uh_sum, &nk->addr[pd->sidx],
			    nk->port[pd->sidx], 1, pd->af);

		if (PF_ANEQ(pd->dst, &nk->addr[pd->didx], pd->af) ||
		    nk->port[pd->didx] != uh->uh_dport)
			pf_change_ap(m, pd->dst, &uh->uh_dport, pd->ip_sum,
			    &uh->uh_sum, &nk->addr[pd->didx],
			    nk->port[pd->didx], 1, pd->af);
		m_copyback(m, off, sizeof(*uh), (caddr_t)uh);
	}

	return (PF_PASS);
}