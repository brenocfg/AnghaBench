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
struct socket {scalar_t__ so_pcb; } ;
struct inpcb {long inp_ip_p; int in6p_hops; int in6p_cksum; struct icmp6_filter* in6p_icmp6filt; int /*<<< orphan*/  inp_vflag; } ;
struct icmp6_filter {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ICMP6_FILTER_SETPASSALL (struct icmp6_filter*) ; 
 int /*<<< orphan*/  INP_INFO_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_INFO_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_IPV6 ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PCB ; 
 int /*<<< orphan*/  PRIV_NETINET_RAW ; 
 int /*<<< orphan*/  V_ripcbinfo ; 
 int /*<<< orphan*/  free (struct icmp6_filter*,int /*<<< orphan*/ ) ; 
 int in_pcballoc (struct socket*,int /*<<< orphan*/ *) ; 
 struct icmp6_filter* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rip_recvspace ; 
 int /*<<< orphan*/  rip_sendspace ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
rip6_attach(struct socket *so, int proto, struct thread *td)
{
	struct inpcb *inp;
	struct icmp6_filter *filter;
	int error;

	inp = sotoinpcb(so);
	KASSERT(inp == NULL, ("rip6_attach: inp != NULL"));

	error = priv_check(td, PRIV_NETINET_RAW);
	if (error)
		return (error);
	error = soreserve(so, rip_sendspace, rip_recvspace);
	if (error)
		return (error);
	filter = malloc(sizeof(struct icmp6_filter), M_PCB, M_NOWAIT);
	if (filter == NULL)
		return (ENOMEM);
	INP_INFO_WLOCK(&V_ripcbinfo);
	error = in_pcballoc(so, &V_ripcbinfo);
	if (error) {
		INP_INFO_WUNLOCK(&V_ripcbinfo);
		free(filter, M_PCB);
		return (error);
	}
	inp = (struct inpcb *)so->so_pcb;
	INP_INFO_WUNLOCK(&V_ripcbinfo);
	inp->inp_vflag |= INP_IPV6;
	inp->inp_ip_p = (long)proto;
	inp->in6p_hops = -1;	/* use kernel default */
	inp->in6p_cksum = -1;
	inp->in6p_icmp6filt = filter;
	ICMP6_FILTER_SETPASSALL(inp->in6p_icmp6filt);
	INP_WUNLOCK(inp);
	return (0);
}