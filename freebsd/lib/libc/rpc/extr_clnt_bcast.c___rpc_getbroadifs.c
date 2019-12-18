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
struct sockaddr_in6 {int sin6_family; int sin6_len; int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct ifaddrs {int ifa_flags; TYPE_2__* ifa_broadaddr; int /*<<< orphan*/  ifa_name; TYPE_1__* ifa_addr; struct ifaddrs* ifa_next; } ;
struct broadif {int /*<<< orphan*/  index; int /*<<< orphan*/  broadaddr; } ;
struct addrinfo {int ai_family; int ai_protocol; int ai_socktype; scalar_t__ ai_addr; } ;
typedef  int /*<<< orphan*/  broadlist_t ;
struct TYPE_4__ {scalar_t__ sa_len; } ;
struct TYPE_3__ {int sa_family; } ;

/* Variables and functions */
 int AF_INET6 ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_UP ; 
 int /*<<< orphan*/  RPCB_MULTICAST_ADDR ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct broadif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct broadif*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getaddrinfo (int /*<<< orphan*/ *,char*,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 int /*<<< orphan*/  if_nametoindex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_pton (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 

int
__rpc_getbroadifs(int af, int proto, int socktype, broadlist_t *list)
{
	int count = 0;
	struct broadif *bip;
	struct ifaddrs *ifap, *ifp;
#ifdef INET6
	struct sockaddr_in6 *sin6;
#endif
	struct sockaddr_in *sin;
	struct addrinfo hints, *res;

	if (getifaddrs(&ifp) < 0)
		return 0;

	memset(&hints, 0, sizeof hints);

	hints.ai_family = af;
	hints.ai_protocol = proto;
	hints.ai_socktype = socktype;

	if (getaddrinfo(NULL, "sunrpc", &hints, &res) != 0) {
		freeifaddrs(ifp);
		return 0;
	}

	for (ifap = ifp; ifap != NULL; ifap = ifap->ifa_next) {
		if (ifap->ifa_addr->sa_family != af ||
		    !(ifap->ifa_flags & IFF_UP))
			continue;
		bip = (struct broadif *)malloc(sizeof *bip);
		if (bip == NULL)
			break;
		bip->index = if_nametoindex(ifap->ifa_name);
		if (
#ifdef INET6
		af != AF_INET6 &&
#endif
		(ifap->ifa_flags & IFF_BROADCAST) &&
		 ifap->ifa_broadaddr) {
			memcpy(&bip->broadaddr, ifap->ifa_broadaddr,
			    (size_t)ifap->ifa_broadaddr->sa_len);
			sin = (struct sockaddr_in *)(void *)&bip->broadaddr;
			sin->sin_port =
			    ((struct sockaddr_in *)
			    (void *)res->ai_addr)->sin_port;
		} else
#ifdef INET6
		if (af == AF_INET6 && (ifap->ifa_flags & IFF_MULTICAST)) {
			sin6 = (struct sockaddr_in6 *)(void *)&bip->broadaddr;
			inet_pton(af, RPCB_MULTICAST_ADDR, &sin6->sin6_addr);
			sin6->sin6_family = af;
			sin6->sin6_len = sizeof *sin6;
			sin6->sin6_port =
			    ((struct sockaddr_in6 *)
			    (void *)res->ai_addr)->sin6_port;
			sin6->sin6_scope_id = bip->index;
		} else
#endif
		{
			free(bip);
			continue;
		}
		TAILQ_INSERT_TAIL(list, bip, link);
		count++;
	}
	freeifaddrs(ifp);
	freeaddrinfo(res);

	return count;
}