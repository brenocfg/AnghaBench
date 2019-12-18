#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; TYPE_5__ sin6_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_2__ a; } ;
struct TYPE_9__ {TYPE_3__ v; } ;
struct node_host {scalar_t__ af; struct node_host* tail; struct node_host* next; int /*<<< orphan*/  ifindex; TYPE_4__ addr; int /*<<< orphan*/ * ifname; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct addrinfo {scalar_t__ ai_family; scalar_t__ ai_addr; struct addrinfo* ai_next; int /*<<< orphan*/  ai_socktype; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 struct node_host* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_ipmask (struct node_host*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 char* strrchr (char*,char) ; 

struct node_host *
host_dns(const char *s, int v4mask, int v6mask)
{
	struct addrinfo		 hints, *res0, *res;
	struct node_host	*n, *h = NULL;
	int			 error, noalias = 0;
	int			 got4 = 0, got6 = 0;
	char			*p, *ps;

	if ((ps = strdup(s)) == NULL)
		err(1, "host_dns: strdup");
	if ((p = strrchr(ps, ':')) != NULL && !strcmp(p, ":0")) {
		noalias = 1;
		*p = '\0';
	}
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM; /* DUMMY */
	error = getaddrinfo(ps, NULL, &hints, &res0);
	if (error) {
		free(ps);
		return (h);
	}

	for (res = res0; res; res = res->ai_next) {
		if (res->ai_family != AF_INET &&
		    res->ai_family != AF_INET6)
			continue;
		if (noalias) {
			if (res->ai_family == AF_INET) {
				if (got4)
					continue;
				got4 = 1;
			} else {
				if (got6)
					continue;
				got6 = 1;
			}
		}
		n = calloc(1, sizeof(struct node_host));
		if (n == NULL)
			err(1, "host_dns: calloc");
		n->ifname = NULL;
		n->af = res->ai_family;
		if (res->ai_family == AF_INET) {
			memcpy(&n->addr.v.a.addr,
			    &((struct sockaddr_in *)
			    res->ai_addr)->sin_addr.s_addr,
			    sizeof(struct in_addr));
			set_ipmask(n, v4mask);
		} else {
			memcpy(&n->addr.v.a.addr,
			    &((struct sockaddr_in6 *)
			    res->ai_addr)->sin6_addr.s6_addr,
			    sizeof(struct in6_addr));
			n->ifindex =
			    ((struct sockaddr_in6 *)
			    res->ai_addr)->sin6_scope_id;
			set_ipmask(n, v6mask);
		}
		n->next = NULL;
		n->tail = n;
		if (h == NULL)
			h = n;
		else {
			h->tail->next = n;
			h->tail = n;
		}
	}
	freeaddrinfo(res0);
	free(ps);

	return (h);
}