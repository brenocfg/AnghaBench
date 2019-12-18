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
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {int sin6_len; struct in6_addr sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
struct llentry {int /*<<< orphan*/  ln_state; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  sin6 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  LLTABLE6 (struct ifnet*) ; 
 int /*<<< orphan*/  ND6_LLINFO_NOSTATE ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 struct llentry* lltable_alloc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*) ; 

__attribute__((used)) static struct llentry *
nd6_alloc(const struct in6_addr *addr6, int flags, struct ifnet *ifp)
{
	struct sockaddr_in6 sin6;
	struct llentry *ln;

	bzero(&sin6, sizeof(sin6));
	sin6.sin6_len = sizeof(struct sockaddr_in6);
	sin6.sin6_family = AF_INET6;
	sin6.sin6_addr = *addr6;

	ln = lltable_alloc_entry(LLTABLE6(ifp), 0, (struct sockaddr *)&sin6);
	if (ln != NULL)
		ln->ln_state = ND6_LLINFO_NOSTATE;

	return (ln);
}