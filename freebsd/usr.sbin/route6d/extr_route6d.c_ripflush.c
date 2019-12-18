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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_port; } ;
struct netinfo6 {scalar_t__ rip6_metric; scalar_t__ rip6_tag; int /*<<< orphan*/  rip6_plen; int /*<<< orphan*/  rip6_dest; } ;
struct TYPE_3__ {int /*<<< orphan*/  sin6_addr; } ;
struct ifc {int /*<<< orphan*/  ifc_flags; TYPE_1__ ifc_ripsin; int /*<<< orphan*/  ifc_name; } ;
struct TYPE_4__ {struct netinfo6* rip6_nets; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  IFF_UP ; 
 scalar_t__ IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 scalar_t__ NEXTHOP_METRIC ; 
 int /*<<< orphan*/  RIPSIZE (int) ; 
 int dflag ; 
 int /*<<< orphan*/  inet6_n2p (int /*<<< orphan*/ *) ; 
 int ntohs (scalar_t__) ; 
 TYPE_2__* ripbuf ; 
 int sendpacket (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (int,char*,...) ; 
 int /*<<< orphan*/  tracet (int,char*,int,...) ; 

__attribute__((used)) static void
ripflush(struct ifc *ifcp, struct sockaddr_in6 *sin6, int nrt, struct netinfo6 *np)
{
	int i;
	int error;

	if (ifcp)
		tracet(1, "Send(%s): info(%d) to %s.%d\n",
			ifcp->ifc_name, nrt,
			inet6_n2p(&sin6->sin6_addr), ntohs(sin6->sin6_port));
	else
		tracet(1, "Send: info(%d) to %s.%d\n",
			nrt, inet6_n2p(&sin6->sin6_addr), ntohs(sin6->sin6_port));
	if (dflag >= 2) {
		np = ripbuf->rip6_nets;
		for (i = 0; i < nrt; i++, np++) {
			if (np->rip6_metric == NEXTHOP_METRIC) {
				if (IN6_IS_ADDR_UNSPECIFIED(&np->rip6_dest))
					trace(2, "    NextHop reset");
				else {
					trace(2, "    NextHop %s",
						inet6_n2p(&np->rip6_dest));
				}
			} else {
				trace(2, "    %s/%d[%d]",
					inet6_n2p(&np->rip6_dest),
					np->rip6_plen, np->rip6_metric);
			}
			if (np->rip6_tag) {
				trace(2, "  tag=0x%04x",
					ntohs(np->rip6_tag) & 0xffff);
			}
			trace(2, "\n");
		}
	}
	error = sendpacket(sin6, RIPSIZE(nrt));
	if (error == EAFNOSUPPORT) {
		/* Protocol not supported */
		if (ifcp != NULL) {
			tracet(1, "Could not send info to %s (%s): "
			    "set IFF_UP to 0\n",
			    ifcp->ifc_name,
			    inet6_n2p(&ifcp->ifc_ripsin.sin6_addr));
			/* As if down for AF_INET6 */
			ifcp->ifc_flags &= ~IFF_UP;
		} else {
			tracet(1, "Could not send info to %s\n",
			    inet6_n2p(&sin6->sin6_addr));
		}
	}
}