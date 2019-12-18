#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int16_t ;
struct ucred {int dummy; } ;
struct socket {int so_type; TYPE_2__* so_proto; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct label {int dummy; } ;
struct inpcb {int inp_flags; } ;
struct TYPE_4__ {TYPE_1__* pr_domain; } ;
struct TYPE_3__ {int dom_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int INP_LOWPORT ; 
 int PF_INET ; 
 int PF_INET6 ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ portacl_autoport_exempt ; 
 scalar_t__ portacl_enabled ; 
 int rules_check (struct ucred*,int,int,scalar_t__) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
socket_check_bind(struct ucred *cred, struct socket *so,
    struct label *solabel, struct sockaddr *sa)
{
	struct sockaddr_in *sin;
	struct inpcb *inp;
	int family, type;
	u_int16_t port;

	/* Only run if we are enabled. */
	if (portacl_enabled == 0)
		return (0);

	/* Only interested in IPv4 and IPv6 sockets. */
	if (so->so_proto->pr_domain->dom_family != PF_INET &&
	    so->so_proto->pr_domain->dom_family != PF_INET6)
		return (0);

	/* Currently, we don't attempt to deal with SOCK_RAW, etc. */
	if (so->so_type != SOCK_DGRAM &&
	    so->so_type != SOCK_STREAM)
		return (0);

	/* Reject addresses we don't understand; fail closed. */
	if (sa->sa_family != AF_INET && sa->sa_family != AF_INET6)
		return (EINVAL);

	family = so->so_proto->pr_domain->dom_family;
	type = so->so_type;
	sin = (struct sockaddr_in *) sa;
	port = ntohs(sin->sin_port);

	/*
	 * Sockets are frequently bound with a specific IP address but a port
	 * number of '0' to request automatic port allocation.  This is often
	 * desirable as long as IP_PORTRANGELOW isn't set, which might permit
	 * automatic allocation of a "privileged" port.  The autoport exempt
	 * flag exempts port 0 allocation from rule checking as long as a low
	 * port isn't required.
	 */
	if (portacl_autoport_exempt && port == 0) {
		inp = sotoinpcb(so);
		if ((inp->inp_flags & INP_LOWPORT) == 0)
			return (0);
	}

	return (rules_check(cred, family, type, port));
}