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
typedef  char u_char ;
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {int sin6_len; struct in6_addr sin6_addr; void* sin6_family; int /*<<< orphan*/  sin6_scope_id; } ;
struct TYPE_2__ {int rmx_hopcount; } ;
struct rt_msghdr {int rtm_addrs; int rtm_msglen; int /*<<< orphan*/  rtm_inits; TYPE_1__ rtm_rmx; int /*<<< orphan*/  rtm_flags; int /*<<< orphan*/  rtm_pid; scalar_t__ rtm_seq; int /*<<< orphan*/  rtm_version; int /*<<< orphan*/  rtm_type; } ;
struct netinfo6 {int rip6_plen; int rip6_metric; struct in6_addr rip6_dest; } ;
struct riprt {int /*<<< orphan*/  rrt_flags; struct netinfo6 rrt_info; } ;
struct ifc {int /*<<< orphan*/  ifc_index; int /*<<< orphan*/  ifc_mylladdr; } ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 void* AF_INET6 ; 
 int BUFSIZ ; 
 scalar_t__ EEXIST ; 
 scalar_t__ IN6_IS_ADDR_LINKLOCAL (struct in6_addr*) ; 
 int /*<<< orphan*/  Qflag ; 
 int ROUNDUP (int) ; 
 int RTA_DST ; 
 int RTA_GATEWAY ; 
 int RTA_NETMASK ; 
 int /*<<< orphan*/  RTM_ADD ; 
 int /*<<< orphan*/  RTM_VERSION ; 
 int /*<<< orphan*/  RTV_HOPCOUNT ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*,...) ; 
 char* hms () ; 
 char* inet6_n2p (struct in6_addr*) ; 
 int /*<<< orphan*/  inet_ntop (void*,void*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nflag ; 
 int /*<<< orphan*/  pid ; 
 struct in6_addr* plen2mask (int) ; 
 scalar_t__ rtlog ; 
 int /*<<< orphan*/  rtsock ; 
 scalar_t__ seq ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  trace (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  tracet (int,char*,char*,int,char*,int,char*) ; 
 scalar_t__ write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
addroute(struct riprt *rrt,
	const struct in6_addr *gw,
	struct ifc *ifcp)
{
	struct	netinfo6 *np;
	u_char	buf[BUFSIZ], buf1[BUFSIZ], buf2[BUFSIZ];
	struct	rt_msghdr	*rtm;
	struct	sockaddr_in6	*sin6;
	int	len;

	np = &rrt->rrt_info;
	inet_ntop(AF_INET6, (const void *)gw, (char *)buf1, sizeof(buf1));
	inet_ntop(AF_INET6, (void *)&ifcp->ifc_mylladdr, (char *)buf2, sizeof(buf2));
	tracet(1, "ADD: %s/%d gw %s [%d] ifa %s\n",
		inet6_n2p(&np->rip6_dest), np->rip6_plen, buf1,
		np->rip6_metric - 1, buf2);
	if (rtlog)
		fprintf(rtlog, "%s: ADD: %s/%d gw %s [%d] ifa %s\n", hms(),
			inet6_n2p(&np->rip6_dest), np->rip6_plen, buf1,
			np->rip6_metric - 1, buf2);
	if (nflag)
		return 0;

	memset(buf, 0, sizeof(buf));
	rtm = (struct rt_msghdr *)(void *)buf;
	rtm->rtm_type = RTM_ADD;
	rtm->rtm_version = RTM_VERSION;
	rtm->rtm_seq = ++seq;
	rtm->rtm_pid = pid;
	rtm->rtm_flags = rrt->rrt_flags;
	rtm->rtm_flags |= Qflag;
	rtm->rtm_addrs = RTA_DST | RTA_GATEWAY | RTA_NETMASK;
	rtm->rtm_rmx.rmx_hopcount = np->rip6_metric - 1;
	rtm->rtm_inits = RTV_HOPCOUNT;
	sin6 = (struct sockaddr_in6 *)(void *)&buf[sizeof(struct rt_msghdr)];
	/* Destination */
	sin6->sin6_len = sizeof(struct sockaddr_in6);
	sin6->sin6_family = AF_INET6;
	sin6->sin6_addr = np->rip6_dest;
	sin6 = (struct sockaddr_in6 *)(void *)((char *)sin6 + ROUNDUP(sin6->sin6_len));
	/* Gateway */
	sin6->sin6_len = sizeof(struct sockaddr_in6);
	sin6->sin6_family = AF_INET6;
	sin6->sin6_addr = *gw;
	if (IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr))
		sin6->sin6_scope_id = ifcp->ifc_index;
	sin6 = (struct sockaddr_in6 *)(void *)((char *)sin6 + ROUNDUP(sin6->sin6_len));
	/* Netmask */
	sin6->sin6_len = sizeof(struct sockaddr_in6);
	sin6->sin6_family = AF_INET6;
	sin6->sin6_addr = *(plen2mask(np->rip6_plen));
	sin6 = (struct sockaddr_in6 *)(void *)((char *)sin6 + ROUNDUP(sin6->sin6_len));

	len = (char *)sin6 - (char *)buf;
	rtm->rtm_msglen = len;
	if (write(rtsock, buf, len) > 0)
		return 0;

	if (errno == EEXIST) {
		trace(0, "ADD: Route already exists %s/%d gw %s\n",
		    inet6_n2p(&np->rip6_dest), np->rip6_plen, buf1);
		if (rtlog)
			fprintf(rtlog, "ADD: Route already exists %s/%d gw %s\n",
			    inet6_n2p(&np->rip6_dest), np->rip6_plen, buf1);
	} else {
		trace(0, "Can not write to rtsock (addroute): %s\n",
		    strerror(errno));
		if (rtlog)
			fprintf(rtlog, "\tCan not write to rtsock: %s\n",
			    strerror(errno));
	}
	return -1;
}