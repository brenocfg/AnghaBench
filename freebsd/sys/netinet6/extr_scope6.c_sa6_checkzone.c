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
struct sockaddr_in6 {scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {scalar_t__* s6id_list; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 scalar_t__ IN6_IS_ADDR_LOOPBACK (int /*<<< orphan*/ *) ; 
 scalar_t__ IN6_IS_ADDR_MULTICAST (int /*<<< orphan*/ *) ; 
 int IPV6_ADDR_SCOPE_GLOBAL ; 
 int IPV6_ADDR_SCOPE_INTFACELOCAL ; 
 int IPV6_ADDR_SCOPE_LINKLOCAL ; 
 scalar_t__ V_ip6_use_defzone ; 
 int /*<<< orphan*/  V_loif ; 
 TYPE_1__ V_sid_default ; 
 int in6_addrscope (int /*<<< orphan*/ *) ; 
 scalar_t__ in6_getscopezone (int /*<<< orphan*/ ,int) ; 

int
sa6_checkzone(struct sockaddr_in6 *sa6)
{
	int scope;

	scope = in6_addrscope(&sa6->sin6_addr);
	if (scope == IPV6_ADDR_SCOPE_GLOBAL)
		return (sa6->sin6_scope_id ? EINVAL: 0);
	if (IN6_IS_ADDR_MULTICAST(&sa6->sin6_addr) &&
	    scope != IPV6_ADDR_SCOPE_LINKLOCAL &&
	    scope != IPV6_ADDR_SCOPE_INTFACELOCAL) {
		if (sa6->sin6_scope_id == 0 && V_ip6_use_defzone != 0)
			sa6->sin6_scope_id = V_sid_default.s6id_list[scope];
		return (0);
	}
	/*
	 * Since ::1 address always configured on the lo0, we can
	 * automatically set its zone id, when it is not specified.
	 * Return error, when specified zone id doesn't match with
	 * actual value.
	 */
	if (IN6_IS_ADDR_LOOPBACK(&sa6->sin6_addr)) {
		if (sa6->sin6_scope_id == 0)
			sa6->sin6_scope_id = in6_getscopezone(V_loif, scope);
		else if (sa6->sin6_scope_id != in6_getscopezone(V_loif, scope))
			return (EADDRNOTAVAIL);
	}
	/* XXX: we can validate sin6_scope_id here */
	if (sa6->sin6_scope_id != 0)
		return (0);
	if (V_ip6_use_defzone != 0)
		sa6->sin6_scope_id = V_sid_default.s6id_list[scope];
	/* Return error if we can't determine zone id */
	return (sa6->sin6_scope_id ? 0: EADDRNOTAVAIL);
}