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
struct tcphdr {int dummy; } ;
struct inpcb {int inp_flags; } ;
struct in_conninfo {int inc_flags; int /*<<< orphan*/  inc_lport; int /*<<< orphan*/  inc_laddr; int /*<<< orphan*/  inc_fport; int /*<<< orphan*/  inc_faddr; int /*<<< orphan*/  inc6_laddr; int /*<<< orphan*/  inc6_faddr; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int INC_ISIPV6 ; 
 int /*<<< orphan*/  INPLOOKUP_WLOCKPCB ; 
 int INP_TIMEWAIT ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  V_tcbinfo ; 
 struct inpcb* in6_pcblookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifnet*) ; 
 struct inpcb* in_pcblookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifnet*) ; 
 int /*<<< orphan*/  tcp_twcheck (struct inpcb*,int /*<<< orphan*/ *,struct tcphdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
toe_4tuple_check(struct in_conninfo *inc, struct tcphdr *th, struct ifnet *ifp)
{
	struct inpcb *inp;

	if (inc->inc_flags & INC_ISIPV6) {
		inp = in6_pcblookup(&V_tcbinfo, &inc->inc6_faddr,
		    inc->inc_fport, &inc->inc6_laddr, inc->inc_lport,
		    INPLOOKUP_WLOCKPCB, ifp);
	} else {
		inp = in_pcblookup(&V_tcbinfo, inc->inc_faddr, inc->inc_fport,
		    inc->inc_laddr, inc->inc_lport, INPLOOKUP_WLOCKPCB, ifp);
	}
	if (inp != NULL) {
		INP_WLOCK_ASSERT(inp);

		if ((inp->inp_flags & INP_TIMEWAIT) && th != NULL) {
			if (!tcp_twcheck(inp, NULL, th, NULL, 0))
				return (EADDRINUSE);
		} else {
			INP_WUNLOCK(inp);
			return (EADDRINUSE);
		}
	}

	return (0);
}