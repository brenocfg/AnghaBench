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
struct sockaddr_in6 {scalar_t__ sin6_family; scalar_t__ sin6_port; scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {int sa_len; } ;
struct inpcb {int /*<<< orphan*/  inp_cred; int /*<<< orphan*/  in6p_outputopts; int /*<<< orphan*/  inp_pcbinfo; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CK_STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int EADDRNOTAVAIL ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 scalar_t__ IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_HASH_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  V_in6_ifaddrhead ; 
 int /*<<< orphan*/  V_ip6_use_defzone ; 
 int in6_selectsrc_socket (struct sockaddr_in6*,int /*<<< orphan*/ ,struct inpcb*,int /*<<< orphan*/ ,int,struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in6addr_loopback ; 
 int prison_remote_ip6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sa6_embedscope (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
in6_pcbladdr(struct inpcb *inp, struct sockaddr *nam,
    struct in6_addr *plocal_addr6)
{
	struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)nam;
	int error = 0;
	int scope_ambiguous = 0;
	struct in6_addr in6a;

	INP_WLOCK_ASSERT(inp);
	INP_HASH_WLOCK_ASSERT(inp->inp_pcbinfo);	/* XXXRW: why? */

	if (nam->sa_len != sizeof (*sin6))
		return (EINVAL);
	if (sin6->sin6_family != AF_INET6)
		return (EAFNOSUPPORT);
	if (sin6->sin6_port == 0)
		return (EADDRNOTAVAIL);

	if (sin6->sin6_scope_id == 0 && !V_ip6_use_defzone)
		scope_ambiguous = 1;
	if ((error = sa6_embedscope(sin6, V_ip6_use_defzone)) != 0)
		return(error);

	if (!CK_STAILQ_EMPTY(&V_in6_ifaddrhead)) {
		/*
		 * If the destination address is UNSPECIFIED addr,
		 * use the loopback addr, e.g ::1.
		 */
		if (IN6_IS_ADDR_UNSPECIFIED(&sin6->sin6_addr))
			sin6->sin6_addr = in6addr_loopback;
	}
	if ((error = prison_remote_ip6(inp->inp_cred, &sin6->sin6_addr)) != 0)
		return (error);

	error = in6_selectsrc_socket(sin6, inp->in6p_outputopts,
	    inp, inp->inp_cred, scope_ambiguous, &in6a, NULL);
	if (error)
		return (error);

	/*
	 * Do not update this earlier, in case we return with an error.
	 *
	 * XXX: this in6_selectsrc_socket result might replace the bound local
	 * address with the address specified by setsockopt(IPV6_PKTINFO).
	 * Is it the intended behavior?
	 */
	*plocal_addr6 = in6a;

	/*
	 * Don't do pcblookup call here; return interface in
	 * plocal_addr6
	 * and exit to caller, that will do the lookup.
	 */

	return (0);
}