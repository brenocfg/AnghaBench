#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ucred {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {int dummy; } ;
struct mbuf {int dummy; } ;
struct inpcbinfo {int dummy; } ;
struct in6_addr {int dummy; } ;
struct inpcb {scalar_t__ inp_lport; int inp_flow; int inp_flags; int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  in6p_faddr; struct in6_addr in6p_laddr; struct inpcbinfo* inp_pcbinfo; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int IN6P_AUTOFLOWLABEL ; 
 scalar_t__ IN6_IS_ADDR_UNSPECIFIED (struct in6_addr*) ; 
 int /*<<< orphan*/  INP_HASH_WLOCK_ASSERT (struct inpcbinfo*) ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int IPV6_FLOWLABEL_MASK ; 
 int htonl (int /*<<< orphan*/ ) ; 
 int in6_pcbbind (struct inpcb*,struct sockaddr*,struct ucred*) ; 
 int in6_pcbladdr (struct inpcb*,struct sockaddr*,struct in6_addr*) ; 
 int /*<<< orphan*/ * in6_pcblookup_hash_locked (struct inpcbinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct in6_addr*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_pcbrehash_mbuf (struct inpcb*,struct mbuf*) ; 
 int /*<<< orphan*/  ip6_randomflowlabel () ; 

int
in6_pcbconnect_mbuf(struct inpcb *inp, struct sockaddr *nam,
    struct ucred *cred, struct mbuf *m)
{
	struct inpcbinfo *pcbinfo = inp->inp_pcbinfo;
	struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)nam;
	struct in6_addr addr6;
	int error;

	INP_WLOCK_ASSERT(inp);
	INP_HASH_WLOCK_ASSERT(pcbinfo);

	/*
	 * Call inner routine, to assign local interface address.
	 * in6_pcbladdr() may automatically fill in sin6_scope_id.
	 */
	if ((error = in6_pcbladdr(inp, nam, &addr6)) != 0)
		return (error);

	if (in6_pcblookup_hash_locked(pcbinfo, &sin6->sin6_addr,
			       sin6->sin6_port,
			      IN6_IS_ADDR_UNSPECIFIED(&inp->in6p_laddr)
			      ? &addr6 : &inp->in6p_laddr,
			      inp->inp_lport, 0, NULL) != NULL) {
		return (EADDRINUSE);
	}
	if (IN6_IS_ADDR_UNSPECIFIED(&inp->in6p_laddr)) {
		if (inp->inp_lport == 0) {
			error = in6_pcbbind(inp, (struct sockaddr *)0, cred);
			if (error)
				return (error);
		}
		inp->in6p_laddr = addr6;
	}
	inp->in6p_faddr = sin6->sin6_addr;
	inp->inp_fport = sin6->sin6_port;
	/* update flowinfo - draft-itojun-ipv6-flowlabel-api-00 */
	inp->inp_flow &= ~IPV6_FLOWLABEL_MASK;
	if (inp->inp_flags & IN6P_AUTOFLOWLABEL)
		inp->inp_flow |=
		    (htonl(ip6_randomflowlabel()) & IPV6_FLOWLABEL_MASK);

	in_pcbrehash_mbuf(inp, m);

	return (0);
}