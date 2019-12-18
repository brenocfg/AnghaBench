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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct socket {int dummy; } ;
struct sockaddr_in6 {scalar_t__ sin6_family; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {int sa_len; } ;
struct inpcb {int /*<<< orphan*/  in6p_laddr; } ;
struct in6_ifaddr {int ia6_flags; } ;
struct ifaddr {int dummy; } ;
struct epoch_tracker {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ CK_STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int IN6_IFF_ANYCAST ; 
 int IN6_IFF_DEPRECATED ; 
 int IN6_IFF_DETACHED ; 
 int IN6_IFF_NOTREADY ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_INFO_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_INFO_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int /*<<< orphan*/  V_ifnet ; 
 int /*<<< orphan*/  V_ip6_use_defzone ; 
 int /*<<< orphan*/  V_ripcbinfo ; 
 struct ifaddr* ifa_ifwithaddr (struct sockaddr*) ; 
 int prison_check_ip6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sa6_embedscope (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
rip6_bind(struct socket *so, struct sockaddr *nam, struct thread *td)
{
	struct epoch_tracker et;
	struct inpcb *inp;
	struct sockaddr_in6 *addr = (struct sockaddr_in6 *)nam;
	struct ifaddr *ifa = NULL;
	int error = 0;

	inp = sotoinpcb(so);
	KASSERT(inp != NULL, ("rip6_bind: inp == NULL"));

	if (nam->sa_len != sizeof(*addr))
		return (EINVAL);
	if ((error = prison_check_ip6(td->td_ucred, &addr->sin6_addr)) != 0)
		return (error);
	if (CK_STAILQ_EMPTY(&V_ifnet) || addr->sin6_family != AF_INET6)
		return (EADDRNOTAVAIL);
	if ((error = sa6_embedscope(addr, V_ip6_use_defzone)) != 0)
		return (error);

	NET_EPOCH_ENTER(et);
	if (!IN6_IS_ADDR_UNSPECIFIED(&addr->sin6_addr) &&
	    (ifa = ifa_ifwithaddr((struct sockaddr *)addr)) == NULL) {
		NET_EPOCH_EXIT(et);
		return (EADDRNOTAVAIL);
	}
	if (ifa != NULL &&
	    ((struct in6_ifaddr *)ifa)->ia6_flags &
	    (IN6_IFF_ANYCAST|IN6_IFF_NOTREADY|
	     IN6_IFF_DETACHED|IN6_IFF_DEPRECATED)) {
		NET_EPOCH_EXIT(et);
		return (EADDRNOTAVAIL);
	}
	NET_EPOCH_EXIT(et);
	INP_INFO_WLOCK(&V_ripcbinfo);
	INP_WLOCK(inp);
	inp->in6p_laddr = addr->sin6_addr;
	INP_WUNLOCK(inp);
	INP_INFO_WUNLOCK(&V_ripcbinfo);
	return (0);
}