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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr_ib {int /*<<< orphan*/  sib_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int ib_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ipv6_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cma_addr_cmp(struct sockaddr *src, struct sockaddr *dst)
{
	if (src->sa_family != dst->sa_family)
		return -1;

	switch (src->sa_family) {
	case AF_INET:
		return ((struct sockaddr_in *) src)->sin_addr.s_addr !=
		       ((struct sockaddr_in *) dst)->sin_addr.s_addr;
	case AF_INET6:
		return ipv6_addr_cmp(&((struct sockaddr_in6 *) src)->sin6_addr,
				     &((struct sockaddr_in6 *) dst)->sin6_addr);
	default:
		return ib_addr_cmp(&((struct sockaddr_ib *) src)->sib_addr,
				   &((struct sockaddr_ib *) dst)->sib_addr);
	}
}