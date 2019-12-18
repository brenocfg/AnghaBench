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
typedef  int /*<<< orphan*/  u_char ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct socket {TYPE_1__* so_proto; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct inpcbinfo {int dummy; } ;
struct inpcb {int inp_flags; int /*<<< orphan*/  inp_vflag; } ;
struct TYPE_2__ {int /*<<< orphan*/  pr_protocol; } ;

/* Variables and functions */
 int IN6P_IPV6_V6ONLY ; 
 scalar_t__ IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 scalar_t__ IN6_IS_ADDR_V4MAPPED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_HASH_WLOCK (struct inpcbinfo*) ; 
 int /*<<< orphan*/  INP_HASH_WUNLOCK (struct inpcbinfo*) ; 
 int /*<<< orphan*/  INP_IPV4 ; 
 int /*<<< orphan*/  INP_IPV6 ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int in6_pcbbind (struct inpcb*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_sin6_2_sin (struct sockaddr_in*,struct sockaddr_in6*) ; 
 int in_pcbbind (struct inpcb*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 struct inpcbinfo* udp_get_inpcbinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
udp6_bind(struct socket *so, struct sockaddr *nam, struct thread *td)
{
	struct inpcb *inp;
	struct inpcbinfo *pcbinfo;
	int error;
	u_char vflagsav;

	pcbinfo = udp_get_inpcbinfo(so->so_proto->pr_protocol);
	inp = sotoinpcb(so);
	KASSERT(inp != NULL, ("udp6_bind: inp == NULL"));

	INP_WLOCK(inp);
	INP_HASH_WLOCK(pcbinfo);
	vflagsav = inp->inp_vflag;
	inp->inp_vflag &= ~INP_IPV4;
	inp->inp_vflag |= INP_IPV6;
	if ((inp->inp_flags & IN6P_IPV6_V6ONLY) == 0) {
		struct sockaddr_in6 *sin6_p;

		sin6_p = (struct sockaddr_in6 *)nam;

		if (IN6_IS_ADDR_UNSPECIFIED(&sin6_p->sin6_addr))
			inp->inp_vflag |= INP_IPV4;
#ifdef INET
		else if (IN6_IS_ADDR_V4MAPPED(&sin6_p->sin6_addr)) {
			struct sockaddr_in sin;

			in6_sin6_2_sin(&sin, sin6_p);
			inp->inp_vflag |= INP_IPV4;
			inp->inp_vflag &= ~INP_IPV6;
			error = in_pcbbind(inp, (struct sockaddr *)&sin,
			    td->td_ucred);
			goto out;
		}
#endif
	}

	error = in6_pcbbind(inp, nam, td->td_ucred);
#ifdef INET
out:
#endif
	if (error != 0)
		inp->inp_vflag = vflagsav;
	INP_HASH_WUNLOCK(pcbinfo);
	INP_WUNLOCK(inp);
	return (error);
}