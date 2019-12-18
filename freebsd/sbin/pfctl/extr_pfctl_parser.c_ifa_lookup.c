#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pf_addr {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  v6; } ;
struct TYPE_7__ {TYPE_4__ mask; TYPE_4__ addr; } ;
struct TYPE_8__ {TYPE_1__ a; } ;
struct TYPE_9__ {TYPE_2__ v; } ;
struct node_host {scalar_t__ af; int ifa_flags; scalar_t__ ifindex; char* ifname; struct node_host* tail; struct node_host* next; TYPE_3__ addr; TYPE_4__ peer; TYPE_4__ bcast; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int IFF_BROADCAST ; 
 int IFF_LINK1 ; 
 int IFF_LOOPBACK ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 scalar_t__ IN6_IS_ADDR_LINKLOCAL (int /*<<< orphan*/ *) ; 
 int PFI_AFLAG_BROADCAST ; 
 int PFI_AFLAG_NETWORK ; 
 int PFI_AFLAG_NOALIAS ; 
 int PFI_AFLAG_PEER ; 
 struct node_host* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 struct node_host* ifa_grouplookup (char*,int) ; 
 int /*<<< orphan*/  ifa_load () ; 
 scalar_t__ ifa_skip_if (char*,struct node_host*) ; 
 struct node_host* iftab ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  set_ipmask (struct node_host*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int unmask (TYPE_4__*,scalar_t__) ; 

struct node_host *
ifa_lookup(char *ifa_name, int flags)
{
	struct node_host	*p = NULL, *h = NULL, *n = NULL;
	int			 got4 = 0, got6 = 0;
	const char		 *last_if = NULL;

	if ((h = ifa_grouplookup(ifa_name, flags)) != NULL)
		return (h);

	if (!strncmp(ifa_name, "self", IFNAMSIZ))
		ifa_name = NULL;

	if (iftab == NULL)
		ifa_load();

	for (p = iftab; p; p = p->next) {
		if (ifa_skip_if(ifa_name, p))
			continue;
		if ((flags & PFI_AFLAG_BROADCAST) && p->af != AF_INET)
			continue;
		if ((flags & PFI_AFLAG_BROADCAST) &&
		    !(p->ifa_flags & IFF_BROADCAST))
			continue;
		if ((flags & PFI_AFLAG_PEER) &&
		    !(p->ifa_flags & IFF_POINTOPOINT))
			continue;
		if ((flags & PFI_AFLAG_NETWORK) && p->ifindex > 0)
			continue;
		if (last_if == NULL || strcmp(last_if, p->ifname))
			got4 = got6 = 0;
		last_if = p->ifname;
		if ((flags & PFI_AFLAG_NOALIAS) && p->af == AF_INET && got4)
			continue;
		if ((flags & PFI_AFLAG_NOALIAS) && p->af == AF_INET6 &&
		    IN6_IS_ADDR_LINKLOCAL(&p->addr.v.a.addr.v6))
			continue;
		if ((flags & PFI_AFLAG_NOALIAS) && p->af == AF_INET6 && got6)
			continue;
		if (p->af == AF_INET)
			got4 = 1;
		else
			got6 = 1;
		n = calloc(1, sizeof(struct node_host));
		if (n == NULL)
			err(1, "address: calloc");
		n->af = p->af;
		if (flags & PFI_AFLAG_BROADCAST)
			memcpy(&n->addr.v.a.addr, &p->bcast,
			    sizeof(struct pf_addr));
		else if (flags & PFI_AFLAG_PEER)
			memcpy(&n->addr.v.a.addr, &p->peer,
			    sizeof(struct pf_addr));
		else
			memcpy(&n->addr.v.a.addr, &p->addr.v.a.addr,
			    sizeof(struct pf_addr));
		if (flags & PFI_AFLAG_NETWORK)
			set_ipmask(n, unmask(&p->addr.v.a.mask, n->af));
		else {
			if (n->af == AF_INET) {
				if (p->ifa_flags & IFF_LOOPBACK &&
				    p->ifa_flags & IFF_LINK1)
					memcpy(&n->addr.v.a.mask,
					    &p->addr.v.a.mask,
					    sizeof(struct pf_addr));
				else
					set_ipmask(n, 32);
			} else
				set_ipmask(n, 128);
		}
		n->ifindex = p->ifindex;
		n->ifname = strdup(p->ifname);

		n->next = NULL;
		n->tail = n;
		if (h == NULL)
			h = n;
		else {
			h->tail->next = n;
			h->tail = n;
		}
	}
	return (h);
}