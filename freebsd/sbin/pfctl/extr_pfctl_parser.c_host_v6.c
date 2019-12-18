#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {TYPE_1__ a; } ;
struct TYPE_6__ {TYPE_2__ v; } ;
struct node_host {struct node_host* tail; int /*<<< orphan*/ * next; int /*<<< orphan*/  ifindex; TYPE_3__ addr; void* af; int /*<<< orphan*/ * ifname; } ;
struct addrinfo {scalar_t__ ai_addr; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_socktype; void* ai_family; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 void* AF_INET6 ; 
 int /*<<< orphan*/  AI_NUMERICHOST ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 struct node_host* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_ipmask (struct node_host*,int) ; 

struct node_host *
host_v6(const char *s, int mask)
{
	struct addrinfo		 hints, *res;
	struct node_host	*h = NULL;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_DGRAM; /*dummy*/
	hints.ai_flags = AI_NUMERICHOST;
	if (getaddrinfo(s, "0", &hints, &res) == 0) {
		h = calloc(1, sizeof(struct node_host));
		if (h == NULL)
			err(1, "address: calloc");
		h->ifname = NULL;
		h->af = AF_INET6;
		memcpy(&h->addr.v.a.addr,
		    &((struct sockaddr_in6 *)res->ai_addr)->sin6_addr,
		    sizeof(h->addr.v.a.addr));
		h->ifindex =
		    ((struct sockaddr_in6 *)res->ai_addr)->sin6_scope_id;
		set_ipmask(h, mask);
		freeaddrinfo(res);
		h->next = NULL;
		h->tail = h;
	}

	return (h);
}