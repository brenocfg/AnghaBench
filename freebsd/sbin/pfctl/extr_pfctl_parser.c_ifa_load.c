#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int* s6_addr; } ;
struct sockaddr_in6 {scalar_t__ sin6_scope_id; TYPE_6__ sin6_addr; } ;
struct TYPE_7__ {int* s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {TYPE_2__ a; } ;
struct TYPE_10__ {TYPE_3__ v; } ;
struct node_host {scalar_t__ af; int ifindex; struct node_host* tail; struct node_host* next; int /*<<< orphan*/ * ifname; int /*<<< orphan*/  peer; int /*<<< orphan*/  bcast; TYPE_4__ addr; int /*<<< orphan*/  ifa_flags; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ifaddrs {int /*<<< orphan*/  ifa_name; TYPE_5__* ifa_addr; int /*<<< orphan*/ * ifa_dstaddr; int /*<<< orphan*/ * ifa_broadaddr; scalar_t__ ifa_netmask; int /*<<< orphan*/  ifa_flags; struct ifaddrs* ifa_next; } ;
struct TYPE_11__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_LINK ; 
 scalar_t__ IN6_IS_ADDR_LINKLOCAL (TYPE_6__*) ; 
 struct node_host* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 int /*<<< orphan*/  ifa_add_groups_to_map (int /*<<< orphan*/ ) ; 
 struct node_host* iftab ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int**,int) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ) ; 

void
ifa_load(void)
{
	struct ifaddrs		*ifap, *ifa;
	struct node_host	*n = NULL, *h = NULL;

	if (getifaddrs(&ifap) < 0)
		err(1, "getifaddrs");

	for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
		if (!(ifa->ifa_addr->sa_family == AF_INET ||
		    ifa->ifa_addr->sa_family == AF_INET6 ||
		    ifa->ifa_addr->sa_family == AF_LINK))
				continue;
		n = calloc(1, sizeof(struct node_host));
		if (n == NULL)
			err(1, "address: calloc");
		n->af = ifa->ifa_addr->sa_family;
		n->ifa_flags = ifa->ifa_flags;
#ifdef __KAME__
		if (n->af == AF_INET6 &&
		    IN6_IS_ADDR_LINKLOCAL(&((struct sockaddr_in6 *)
		    ifa->ifa_addr)->sin6_addr) &&
		    ((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_scope_id ==
		    0) {
			struct sockaddr_in6	*sin6;

			sin6 = (struct sockaddr_in6 *)ifa->ifa_addr;
			sin6->sin6_scope_id = sin6->sin6_addr.s6_addr[2] << 8 |
			    sin6->sin6_addr.s6_addr[3];
			sin6->sin6_addr.s6_addr[2] = 0;
			sin6->sin6_addr.s6_addr[3] = 0;
		}
#endif
		n->ifindex = 0;
		if (n->af == AF_INET) {
			memcpy(&n->addr.v.a.addr, &((struct sockaddr_in *)
			    ifa->ifa_addr)->sin_addr.s_addr,
			    sizeof(struct in_addr));
			memcpy(&n->addr.v.a.mask, &((struct sockaddr_in *)
			    ifa->ifa_netmask)->sin_addr.s_addr,
			    sizeof(struct in_addr));
			if (ifa->ifa_broadaddr != NULL)
				memcpy(&n->bcast, &((struct sockaddr_in *)
				    ifa->ifa_broadaddr)->sin_addr.s_addr,
				    sizeof(struct in_addr));
			if (ifa->ifa_dstaddr != NULL)
				memcpy(&n->peer, &((struct sockaddr_in *)
				    ifa->ifa_dstaddr)->sin_addr.s_addr,
				    sizeof(struct in_addr));
		} else if (n->af == AF_INET6) {
			memcpy(&n->addr.v.a.addr, &((struct sockaddr_in6 *)
			    ifa->ifa_addr)->sin6_addr.s6_addr,
			    sizeof(struct in6_addr));
			memcpy(&n->addr.v.a.mask, &((struct sockaddr_in6 *)
			    ifa->ifa_netmask)->sin6_addr.s6_addr,
			    sizeof(struct in6_addr));
			if (ifa->ifa_broadaddr != NULL)
				memcpy(&n->bcast, &((struct sockaddr_in6 *)
				    ifa->ifa_broadaddr)->sin6_addr.s6_addr,
				    sizeof(struct in6_addr));
			if (ifa->ifa_dstaddr != NULL)
				 memcpy(&n->peer, &((struct sockaddr_in6 *)
				    ifa->ifa_dstaddr)->sin6_addr.s6_addr,
				    sizeof(struct in6_addr));
			n->ifindex = ((struct sockaddr_in6 *)
			    ifa->ifa_addr)->sin6_scope_id;
		} else if (n->af == AF_LINK) {
			ifa_add_groups_to_map(ifa->ifa_name);
		}
		if ((n->ifname = strdup(ifa->ifa_name)) == NULL)
			err(1, "ifa_load: strdup");
		n->next = NULL;
		n->tail = n;
		if (h == NULL)
			h = n;
		else {
			h->tail->next = n;
			h->tail = n;
		}
	}

	iftab = h;
	freeifaddrs(ifap);
}