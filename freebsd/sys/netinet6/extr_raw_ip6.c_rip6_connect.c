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
struct thread {int dummy; } ;
struct socket {int /*<<< orphan*/  so_cred; } ;
struct sockaddr_in6 {scalar_t__ sin6_family; scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {int sa_len; } ;
struct in6_addr {int dummy; } ;
struct inpcb {struct in6_addr in6p_laddr; int /*<<< orphan*/  in6p_faddr; int /*<<< orphan*/  in6p_outputopts; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ CK_STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int EADDRNOTAVAIL ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  INP_INFO_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_INFO_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  V_ifnet ; 
 int /*<<< orphan*/  V_ip6_use_defzone ; 
 int /*<<< orphan*/  V_ripcbinfo ; 
 int in6_selectsrc_socket (struct sockaddr_in6*,int /*<<< orphan*/ ,struct inpcb*,int /*<<< orphan*/ ,int,struct in6_addr*,int /*<<< orphan*/ *) ; 
 int sa6_embedscope (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soisconnected (struct socket*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
rip6_connect(struct socket *so, struct sockaddr *nam, struct thread *td)
{
	struct inpcb *inp;
	struct sockaddr_in6 *addr = (struct sockaddr_in6 *)nam;
	struct in6_addr in6a;
	int error = 0, scope_ambiguous = 0;

	inp = sotoinpcb(so);
	KASSERT(inp != NULL, ("rip6_connect: inp == NULL"));

	if (nam->sa_len != sizeof(*addr))
		return (EINVAL);
	if (CK_STAILQ_EMPTY(&V_ifnet))
		return (EADDRNOTAVAIL);
	if (addr->sin6_family != AF_INET6)
		return (EAFNOSUPPORT);

	/*
	 * Application should provide a proper zone ID or the use of default
	 * zone IDs should be enabled.  Unfortunately, some applications do
	 * not behave as it should, so we need a workaround.  Even if an
	 * appropriate ID is not determined, we'll see if we can determine
	 * the outgoing interface.  If we can, determine the zone ID based on
	 * the interface below.
	 */
	if (addr->sin6_scope_id == 0 && !V_ip6_use_defzone)
		scope_ambiguous = 1;
	if ((error = sa6_embedscope(addr, V_ip6_use_defzone)) != 0)
		return (error);

	INP_INFO_WLOCK(&V_ripcbinfo);
	INP_WLOCK(inp);
	/* Source address selection. XXX: need pcblookup? */
	error = in6_selectsrc_socket(addr, inp->in6p_outputopts,
	    inp, so->so_cred, scope_ambiguous, &in6a, NULL);
	if (error) {
		INP_WUNLOCK(inp);
		INP_INFO_WUNLOCK(&V_ripcbinfo);
		return (error);
	}

	inp->in6p_faddr = addr->sin6_addr;
	inp->in6p_laddr = in6a;
	soisconnected(so);
	INP_WUNLOCK(inp);
	INP_INFO_WUNLOCK(&V_ripcbinfo);
	return (0);
}