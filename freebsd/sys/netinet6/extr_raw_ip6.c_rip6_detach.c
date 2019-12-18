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
struct socket {int dummy; } ;
struct inpcb {int /*<<< orphan*/  in6p_icmp6filt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_INFO_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_INFO_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_PCB ; 
 struct socket* V_ip6_mrouter ; 
 int /*<<< orphan*/  V_ripcbinfo ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_pcbdetach (struct inpcb*) ; 
 int /*<<< orphan*/  in_pcbfree (struct inpcb*) ; 
 int /*<<< orphan*/  ip6_mrouter_done () ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static void
rip6_detach(struct socket *so)
{
	struct inpcb *inp;

	inp = sotoinpcb(so);
	KASSERT(inp != NULL, ("rip6_detach: inp == NULL"));

	if (so == V_ip6_mrouter && ip6_mrouter_done)
		ip6_mrouter_done();
	/* xxx: RSVP */
	INP_INFO_WLOCK(&V_ripcbinfo);
	INP_WLOCK(inp);
	free(inp->in6p_icmp6filt, M_PCB);
	in_pcbdetach(inp);
	in_pcbfree(inp);
	INP_INFO_WUNLOCK(&V_ripcbinfo);
}