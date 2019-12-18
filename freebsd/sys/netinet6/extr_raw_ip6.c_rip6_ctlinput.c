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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; int sa_len; } ;
struct ip6ctlparam {struct sockaddr_in6* ip6c_src; void* ip6c_cmdarg; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int PRC_HOSTDEAD ; 
 scalar_t__ PRC_IS_REDIRECT (int) ; 
 unsigned int PRC_NCMDS ; 
 int /*<<< orphan*/  V_ripcbinfo ; 
 int /*<<< orphan*/  in6_pcbnotify (int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ ,struct sockaddr const*,int /*<<< orphan*/ ,int,void*,struct inpcb* (*) (struct inpcb*,int)) ; 
 struct inpcb* in6_rtchange (struct inpcb*,int) ; 
 scalar_t__* inet6ctlerrmap ; 
 struct sockaddr_in6 sa6_any ; 

void
rip6_ctlinput(int cmd, struct sockaddr *sa, void *d)
{
	struct ip6ctlparam *ip6cp = NULL;
	const struct sockaddr_in6 *sa6_src = NULL;
	void *cmdarg;
	struct inpcb *(*notify)(struct inpcb *, int) = in6_rtchange;

	if (sa->sa_family != AF_INET6 ||
	    sa->sa_len != sizeof(struct sockaddr_in6))
		return;

	if ((unsigned)cmd >= PRC_NCMDS)
		return;
	if (PRC_IS_REDIRECT(cmd))
		notify = in6_rtchange, d = NULL;
	else if (cmd == PRC_HOSTDEAD)
		d = NULL;
	else if (inet6ctlerrmap[cmd] == 0)
		return;

	/*
	 * If the parameter is from icmp6, decode it.
	 */
	if (d != NULL) {
		ip6cp = (struct ip6ctlparam *)d;
		cmdarg = ip6cp->ip6c_cmdarg;
		sa6_src = ip6cp->ip6c_src;
	} else {
		cmdarg = NULL;
		sa6_src = &sa6_any;
	}

	(void) in6_pcbnotify(&V_ripcbinfo, sa, 0,
	    (const struct sockaddr *)sa6_src, 0, cmd, cmdarg, notify);
}