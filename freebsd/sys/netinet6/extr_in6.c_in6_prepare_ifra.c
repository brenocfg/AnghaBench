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
struct sockaddr_in6 {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_3__ {int sin6_len; struct in6_addr sin6_addr; void* sin6_family; } ;
struct TYPE_4__ {int sin6_len; struct in6_addr sin6_addr; void* sin6_family; } ;
struct in6_aliasreq {TYPE_1__ ifra_prefixmask; TYPE_2__ ifra_addr; } ;

/* Variables and functions */
 void* AF_INET6 ; 
 int /*<<< orphan*/  memset (struct in6_aliasreq*,int /*<<< orphan*/ ,int) ; 

void
in6_prepare_ifra(struct in6_aliasreq *ifra, const struct in6_addr *addr,
    const struct in6_addr *mask)
{

	memset(ifra, 0, sizeof(struct in6_aliasreq));

	ifra->ifra_addr.sin6_family = AF_INET6;
	ifra->ifra_addr.sin6_len = sizeof(struct sockaddr_in6);
	if (addr != NULL)
		ifra->ifra_addr.sin6_addr = *addr;

	ifra->ifra_prefixmask.sin6_family = AF_INET6;
	ifra->ifra_prefixmask.sin6_len = sizeof(struct sockaddr_in6);
	if (mask != NULL)
		ifra->ifra_prefixmask.sin6_addr = *mask;
}