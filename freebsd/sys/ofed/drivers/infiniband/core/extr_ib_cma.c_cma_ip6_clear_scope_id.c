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
struct in6_addr {scalar_t__* s6_addr; } ;

/* Variables and functions */
 scalar_t__ IN6_IS_ADDR_MC_INTFACELOCAL (struct in6_addr*) ; 
 scalar_t__ IN6_IS_SCOPE_LINKLOCAL (struct in6_addr*) ; 

__attribute__((used)) static void cma_ip6_clear_scope_id(struct in6_addr *addr)
{
	/* make sure link local scope ID gets zeroed */
	if (IN6_IS_SCOPE_LINKLOCAL(addr) ||
	    IN6_IS_ADDR_MC_INTFACELOCAL(addr)) {
		/* use byte-access to be alignment safe */
		addr->s6_addr[2] = 0;
		addr->s6_addr[3] = 0;
	}
}