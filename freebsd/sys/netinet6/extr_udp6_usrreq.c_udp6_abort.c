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
typedef  size_t uint8_t ;
struct socket {TYPE_1__* so_proto; } ;
struct pr_usrreqs {int /*<<< orphan*/  (* pru_abort ) (struct socket*) ;} ;
struct inpcbinfo {int dummy; } ;
struct inpcb {int inp_vflag; int /*<<< orphan*/  in6p_laddr; int /*<<< orphan*/  in6p_faddr; TYPE_3__* inp_socket; } ;
struct TYPE_8__ {struct pr_usrreqs* pr_usrreqs; } ;
struct TYPE_7__ {TYPE_2__* so_proto; } ;
struct TYPE_6__ {scalar_t__ pr_protocol; } ;
struct TYPE_5__ {int /*<<< orphan*/  pr_protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_HASH_WLOCK (struct inpcbinfo*) ; 
 int /*<<< orphan*/  INP_HASH_WUNLOCK (struct inpcbinfo*) ; 
 int INP_IPV4 ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ IPPROTO_UDPLITE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  in6_pcbdisconnect (struct inpcb*) ; 
 int /*<<< orphan*/  in6addr_any ; 
 TYPE_4__* inetsw ; 
 size_t* ip_protox ; 
 int /*<<< orphan*/  soisdisconnected (struct socket*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int /*<<< orphan*/  stub1 (struct socket*) ; 
 struct inpcbinfo* udp_get_inpcbinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
udp6_abort(struct socket *so)
{
	struct inpcb *inp;
	struct inpcbinfo *pcbinfo;

	pcbinfo = udp_get_inpcbinfo(so->so_proto->pr_protocol);
	inp = sotoinpcb(so);
	KASSERT(inp != NULL, ("udp6_abort: inp == NULL"));

	INP_WLOCK(inp);
#ifdef INET
	if (inp->inp_vflag & INP_IPV4) {
		struct pr_usrreqs *pru;
		uint8_t nxt;

		nxt = (inp->inp_socket->so_proto->pr_protocol == IPPROTO_UDP) ?
		    IPPROTO_UDP : IPPROTO_UDPLITE;
		INP_WUNLOCK(inp);
		pru = inetsw[ip_protox[nxt]].pr_usrreqs;
		(*pru->pru_abort)(so);
		return;
	}
#endif

	if (!IN6_IS_ADDR_UNSPECIFIED(&inp->in6p_faddr)) {
		INP_HASH_WLOCK(pcbinfo);
		in6_pcbdisconnect(inp);
		inp->in6p_laddr = in6addr_any;
		INP_HASH_WUNLOCK(pcbinfo);
		soisdisconnected(so);
	}
	INP_WUNLOCK(inp);
}