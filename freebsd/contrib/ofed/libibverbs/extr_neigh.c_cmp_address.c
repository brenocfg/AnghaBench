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
struct TYPE_4__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {TYPE_2__ sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool cmp_address(const struct sockaddr *s1,
			const struct sockaddr *s2)
{
	if (s1->sa_family != s2->sa_family)
		return false;

	switch (s1->sa_family) {
	case AF_INET:
		return ((struct sockaddr_in *)s1)->sin_addr.s_addr ==
		       ((struct sockaddr_in *)s2)->sin_addr.s_addr;
	case AF_INET6:
		return !memcmp(
			((struct sockaddr_in6 *)s1)->sin6_addr.s6_addr,
			((struct sockaddr_in6 *)s2)->sin6_addr.s6_addr,
			sizeof(((struct sockaddr_in6 *)s1)->sin6_addr.s6_addr));
	default:
		return false;
	}
}