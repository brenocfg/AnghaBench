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
struct sockaddr_in6 {scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct rdma_dev_addr {scalar_t__ bound_dev_if; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET_QUIET (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ IN6_IS_ADDR_MC_INTFACELOCAL (int /*<<< orphan*/ *) ; 
 scalar_t__ IN6_IS_SCOPE_LINKLOCAL (int /*<<< orphan*/ *) ; 
 scalar_t__ sa6_recoverscope (struct sockaddr_in6*) ; 

__attribute__((used)) static int cma_check_linklocal(struct rdma_dev_addr *dev_addr,
			       struct sockaddr *addr)
{
#ifdef INET6
	struct sockaddr_in6 sin6;

	if (addr->sa_family != AF_INET6)
		return 0;

	sin6 = *(struct sockaddr_in6 *)addr;

	if (IN6_IS_SCOPE_LINKLOCAL(&sin6.sin6_addr) ||
	    IN6_IS_ADDR_MC_INTFACELOCAL(&sin6.sin6_addr)) {
		bool failure;

		CURVNET_SET_QUIET(dev_addr->net);
		failure = sa6_recoverscope(&sin6) || sin6.sin6_scope_id == 0;
		CURVNET_RESTORE();

		/* check if IPv6 scope ID is not set */
		if (failure)
			return -EINVAL;
		dev_addr->bound_dev_if = sin6.sin6_scope_id;
	}
#endif
	return 0;
}