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
typedef  int /*<<< orphan*/  u16 ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr_ib {int /*<<< orphan*/  sib_sid_mask; int /*<<< orphan*/  sib_sid; } ;
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  AF_IB 130 
#define  AF_INET 129 
#define  AF_INET6 128 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be16 cma_port(struct sockaddr *addr)
{
	struct sockaddr_ib *sib;

	switch (addr->sa_family) {
	case AF_INET:
		return ((struct sockaddr_in *) addr)->sin_port;
	case AF_INET6:
		return ((struct sockaddr_in6 *) addr)->sin6_port;
	case AF_IB:
		sib = (struct sockaddr_ib *) addr;
		return htons((u16) (be64_to_cpu(sib->sib_sid) &
				    be64_to_cpu(sib->sib_sid_mask)));
	default:
		return 0;
	}
}