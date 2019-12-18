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
struct sockaddr_in6 {int dummy; } ;
typedef  struct sockaddr_in6 sockaddr_in ;
struct ipv6_mreq {unsigned int ipv6mr_interface; int /*<<< orphan*/  ipv6mr_multiaddr; } ;
struct ifaddrs {int ifa_flags; int /*<<< orphan*/  ifa_name; TYPE_1__* ifa_addr; struct ifaddrs* ifa_next; } ;
struct addrinfo {int /*<<< orphan*/  ai_addr; scalar_t__ ai_family; } ;
struct TYPE_2__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IPV6_JOIN_GROUP ; 
 int /*<<< orphan*/  RPCB_MULTICAST_ADDR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ debugging ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ *,char*,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 unsigned int if_nametoindex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_pton (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sockaddr_in6* local_in4 ; 
 struct sockaddr_in6* local_in6 ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ipv6_mreq*,int) ; 
 int socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
network_init(void)
{
#ifdef INET6
	struct ifaddrs *ifap, *ifp;
	struct ipv6_mreq mreq6;
	unsigned int ifindex;
	int s;
#endif
	int ecode;
	struct addrinfo hints, *res;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	if ((ecode = getaddrinfo(NULL, "sunrpc", &hints, &res))) {
		if (debugging)
			fprintf(stderr, "can't get local ip4 address: %s\n",
			    gai_strerror(ecode));
	} else {
		local_in4 = (struct sockaddr_in *)malloc(sizeof *local_in4);
		if (local_in4 == NULL) {
			if (debugging)
				fprintf(stderr, "can't alloc local ip4 addr\n");
			exit(1);
		}
		memcpy(local_in4, res->ai_addr, sizeof *local_in4);
		freeaddrinfo(res);
	}

#ifdef INET6
	hints.ai_family = AF_INET6;
	if ((ecode = getaddrinfo(NULL, "sunrpc", &hints, &res))) {
		if (debugging)
			fprintf(stderr, "can't get local ip6 address: %s\n",
			    gai_strerror(ecode));
	} else {
		local_in6 = (struct sockaddr_in6 *)malloc(sizeof *local_in6);
		if (local_in6 == NULL) {
			if (debugging)
				fprintf(stderr, "can't alloc local ip6 addr\n");
			exit(1);
		}
		memcpy(local_in6, res->ai_addr, sizeof *local_in6);
		freeaddrinfo(res);
	}

	/*
	 * Now join the RPC ipv6 multicast group on all interfaces.
	 */
	if (getifaddrs(&ifp) < 0)
		return;

	mreq6.ipv6mr_interface = 0;
	inet_pton(AF_INET6, RPCB_MULTICAST_ADDR, &mreq6.ipv6mr_multiaddr);

	s = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
	if (s == -1) {
		if (debugging)
			fprintf(stderr, "couldn't create ip6 socket");
		goto done_inet6;
	}

	/*
	 * Loop through all interfaces. For each IPv6 multicast-capable
	 * interface, join the RPC multicast group on that interface.
	 */
	for (ifap = ifp; ifap != NULL; ifap = ifap->ifa_next) {
		if (ifap->ifa_addr->sa_family != AF_INET6 ||
		    !(ifap->ifa_flags & IFF_MULTICAST))
			continue;
		ifindex = if_nametoindex(ifap->ifa_name);
		if (ifindex == mreq6.ipv6mr_interface)
			/*
			 * Already did this one.
			 */
			continue;
		mreq6.ipv6mr_interface = ifindex;
		if (setsockopt(s, IPPROTO_IPV6, IPV6_JOIN_GROUP, &mreq6,
		    sizeof mreq6) < 0)
			if (debugging)
				perror("setsockopt v6 multicast");
	}
done_inet6:
	freeifaddrs(ifp);
#endif

	/* close(s); */
}