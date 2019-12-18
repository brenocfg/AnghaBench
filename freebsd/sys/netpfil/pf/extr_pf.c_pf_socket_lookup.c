#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_9__ {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct TYPE_8__ {TYPE_2__* udp; TYPE_1__* tcp; } ;
struct pf_pdesc {int proto; int af; TYPE_4__ lookup; struct pf_addr* src; struct pf_addr* dst; TYPE_3__ hdr; } ;
struct pf_addr {int /*<<< orphan*/  v6; int /*<<< orphan*/  v4; } ;
struct mbuf {int dummy; } ;
struct inpcbinfo {int dummy; } ;
struct inpcb {TYPE_5__* inp_cred; } ;
struct TYPE_10__ {int /*<<< orphan*/ * cr_groups; int /*<<< orphan*/  cr_uid; } ;
struct TYPE_7__ {int /*<<< orphan*/  uh_dport; int /*<<< orphan*/  uh_sport; } ;
struct TYPE_6__ {int /*<<< orphan*/  th_dport; int /*<<< orphan*/  th_sport; } ;

/* Variables and functions */
#define  AF_INET 131 
#define  AF_INET6 130 
 int /*<<< orphan*/  GID_MAX ; 
 int INPLOOKUP_RLOCKPCB ; 
 int INPLOOKUP_WILDCARD ; 
 int /*<<< orphan*/  INP_RLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  INP_RUNLOCK (struct inpcb*) ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int PF_IN ; 
 int /*<<< orphan*/  UID_MAX ; 
 struct inpcbinfo V_tcbinfo ; 
 struct inpcbinfo V_udbinfo ; 
 struct inpcb* in6_pcblookup_mbuf (struct inpcbinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct mbuf*) ; 
 struct inpcb* in_pcblookup_mbuf (struct inpcbinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct mbuf*) ; 

int
pf_socket_lookup(int direction, struct pf_pdesc *pd, struct mbuf *m)
{
	struct pf_addr		*saddr, *daddr;
	u_int16_t		 sport, dport;
	struct inpcbinfo	*pi;
	struct inpcb		*inp;

	pd->lookup.uid = UID_MAX;
	pd->lookup.gid = GID_MAX;

	switch (pd->proto) {
	case IPPROTO_TCP:
		if (pd->hdr.tcp == NULL)
			return (-1);
		sport = pd->hdr.tcp->th_sport;
		dport = pd->hdr.tcp->th_dport;
		pi = &V_tcbinfo;
		break;
	case IPPROTO_UDP:
		if (pd->hdr.udp == NULL)
			return (-1);
		sport = pd->hdr.udp->uh_sport;
		dport = pd->hdr.udp->uh_dport;
		pi = &V_udbinfo;
		break;
	default:
		return (-1);
	}
	if (direction == PF_IN) {
		saddr = pd->src;
		daddr = pd->dst;
	} else {
		u_int16_t	p;

		p = sport;
		sport = dport;
		dport = p;
		saddr = pd->dst;
		daddr = pd->src;
	}
	switch (pd->af) {
#ifdef INET
	case AF_INET:
		inp = in_pcblookup_mbuf(pi, saddr->v4, sport, daddr->v4,
		    dport, INPLOOKUP_RLOCKPCB, NULL, m);
		if (inp == NULL) {
			inp = in_pcblookup_mbuf(pi, saddr->v4, sport,
			   daddr->v4, dport, INPLOOKUP_WILDCARD |
			   INPLOOKUP_RLOCKPCB, NULL, m);
			if (inp == NULL)
				return (-1);
		}
		break;
#endif /* INET */
#ifdef INET6
	case AF_INET6:
		inp = in6_pcblookup_mbuf(pi, &saddr->v6, sport, &daddr->v6,
		    dport, INPLOOKUP_RLOCKPCB, NULL, m);
		if (inp == NULL) {
			inp = in6_pcblookup_mbuf(pi, &saddr->v6, sport,
			    &daddr->v6, dport, INPLOOKUP_WILDCARD |
			    INPLOOKUP_RLOCKPCB, NULL, m);
			if (inp == NULL)
				return (-1);
		}
		break;
#endif /* INET6 */

	default:
		return (-1);
	}
	INP_RLOCK_ASSERT(inp);
	pd->lookup.uid = inp->inp_cred->cr_uid;
	pd->lookup.gid = inp->inp_cred->cr_groups[0];
	INP_RUNLOCK(inp);

	return (1);
}