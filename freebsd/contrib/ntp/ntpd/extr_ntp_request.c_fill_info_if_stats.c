#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* addr; void* addr6; } ;
struct TYPE_8__ {void* addr; void* addr6; } ;
struct TYPE_7__ {void* addr; void* addr6; } ;
struct info_if_stats {int v6_flag; int /*<<< orphan*/  action; void* peercnt; int /*<<< orphan*/  ignore_packets; void* uptime; void* ifnum; void* ifindex; void* scopeid; void* notsent; void* sent; void* received; void* num_mcast; void* last_ttl; void* flags; int /*<<< orphan*/  family; int /*<<< orphan*/  name; TYPE_3__ unmask; TYPE_2__ unbcast; TYPE_1__ unaddr; } ;
struct TYPE_10__ {int /*<<< orphan*/  action; TYPE_5__* ep; } ;
typedef  TYPE_4__ interface_info_t ;
struct TYPE_11__ {int flags; int last_ttl; int num_mcast; int received; int sent; int notsent; int ifindex; int ifnum; int starttime; int peercnt; int /*<<< orphan*/  ignore_packets; int /*<<< orphan*/  family; int /*<<< orphan*/  name; int /*<<< orphan*/  mask; int /*<<< orphan*/  bcast; int /*<<< orphan*/  sin; } ;
typedef  TYPE_5__ endpt ;

/* Variables and functions */
 scalar_t__ IS_IPV6 (int /*<<< orphan*/ *) ; 
 void* SOCK_ADDR4 (int /*<<< orphan*/ *) ; 
 void* SOCK_ADDR6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZERO (struct info_if_stats) ; 
 int /*<<< orphan*/  client_v6_capable ; 
 int current_time ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ more_pkt () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fill_info_if_stats(void *data, interface_info_t *interface_info)
{
	struct info_if_stats **ifsp = (struct info_if_stats **)data;
	struct info_if_stats *ifs = *ifsp;
	endpt *ep = interface_info->ep;

	if (NULL == ifs)
		return;
	
	ZERO(*ifs);
	
	if (IS_IPV6(&ep->sin)) {
		if (!client_v6_capable)
			return;
		ifs->v6_flag = 1;
		ifs->unaddr.addr6 = SOCK_ADDR6(&ep->sin);
		ifs->unbcast.addr6 = SOCK_ADDR6(&ep->bcast);
		ifs->unmask.addr6 = SOCK_ADDR6(&ep->mask);
	} else {
		ifs->v6_flag = 0;
		ifs->unaddr.addr = SOCK_ADDR4(&ep->sin);
		ifs->unbcast.addr = SOCK_ADDR4(&ep->bcast);
		ifs->unmask.addr = SOCK_ADDR4(&ep->mask);
	}
	ifs->v6_flag = htonl(ifs->v6_flag);
	strlcpy(ifs->name, ep->name, sizeof(ifs->name));
	ifs->family = htons(ep->family);
	ifs->flags = htonl(ep->flags);
	ifs->last_ttl = htonl(ep->last_ttl);
	ifs->num_mcast = htonl(ep->num_mcast);
	ifs->received = htonl(ep->received);
	ifs->sent = htonl(ep->sent);
	ifs->notsent = htonl(ep->notsent);
	ifs->ifindex = htonl(ep->ifindex);
	/* scope no longer in endpt, in in6_addr typically */
	ifs->scopeid = ifs->ifindex;
	ifs->ifnum = htonl(ep->ifnum);
	ifs->uptime = htonl(current_time - ep->starttime);
	ifs->ignore_packets = ep->ignore_packets;
	ifs->peercnt = htonl(ep->peercnt);
	ifs->action = interface_info->action;
	
	*ifsp = (struct info_if_stats *)more_pkt();
}