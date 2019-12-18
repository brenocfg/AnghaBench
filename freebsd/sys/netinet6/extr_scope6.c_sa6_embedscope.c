#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * s6_addr16; } ;
struct sockaddr_in6 {int sin6_scope_id; TYPE_1__ sin6_addr; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ IN6_IS_ADDR_MC_INTFACELOCAL (TYPE_1__*) ; 
 scalar_t__ IN6_IS_SCOPE_LINKLOCAL (TYPE_1__*) ; 
 int V_if_index ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/ * ifnet_byindex (int) ; 
 int scope6_addr2default (TYPE_1__*) ; 

int
sa6_embedscope(struct sockaddr_in6 *sin6, int defaultok)
{
	u_int32_t zoneid;

	if ((zoneid = sin6->sin6_scope_id) == 0 && defaultok)
		zoneid = scope6_addr2default(&sin6->sin6_addr);

	if (zoneid != 0 &&
	    (IN6_IS_SCOPE_LINKLOCAL(&sin6->sin6_addr) ||
	    IN6_IS_ADDR_MC_INTFACELOCAL(&sin6->sin6_addr))) {
		/*
		 * At this moment, we only check interface-local and
		 * link-local scope IDs, and use interface indices as the
		 * zone IDs assuming a one-to-one mapping between interfaces
		 * and links.
		 */
		if (V_if_index < zoneid || ifnet_byindex(zoneid) == NULL)
			return (ENXIO);

		/* XXX assignment to 16bit from 32bit variable */
		sin6->sin6_addr.s6_addr16[1] = htons(zoneid & 0xffff);
		sin6->sin6_scope_id = 0;
	}

	return 0;
}