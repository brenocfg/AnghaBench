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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct ip6_rthdr0 {int ip6r0_segleft; } ;
struct addrinfo {scalar_t__ ai_addr; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AI_NUMERICHOST ; 
 int /*<<< orphan*/  IPV6_RTHDR_TYPE_0 ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  checknum (int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo const*,struct addrinfo**) ; 
 int inet6_rth_add (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * inet6_rth_init (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_funcname (char*,int) ; 

void
test_rth_add()
{
	int	i, ret;
	char	buf[10240];
	struct addrinfo *res;
	struct addrinfo hints;

	set_funcname("test_rth_add", sizeof("test_rth_add\0"));

	if (NULL == inet6_rth_init(buf, 10240, IPV6_RTHDR_TYPE_0, 127))
		abort();
	memset((void *)&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET6;
	hints.ai_flags = AI_NUMERICHOST;
	if (0 != getaddrinfo("::1", NULL, (const struct addrinfo *)&hints, &res))
		abort();
	for (i = 0; i < 127; i++)
		inet6_rth_add((void *)buf,
		    &((struct sockaddr_in6 *)(res->ai_addr))->sin6_addr);
	checknum(127, ((struct ip6_rthdr0 *)buf)->ip6r0_segleft, 0,
	    "add 127 segments\0");

	ret = inet6_rth_add((void *)buf,
	    &((struct sockaddr_in6 *)(res->ai_addr))->sin6_addr);
	checknum(-1, ret, 0, "add 128th segment to 127 segment header\0");

	freeaddrinfo(res);
}