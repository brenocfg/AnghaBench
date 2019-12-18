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
struct in6_addr {scalar_t__* s6_addr16; } ;

/* Variables and functions */
 scalar_t__ IN6_IS_ADDR_MC_INTFACELOCAL (struct in6_addr*) ; 
 scalar_t__ IN6_IS_SCOPE_LINKLOCAL (struct in6_addr*) ; 

int
in6_clearscope(struct in6_addr *in6)
{
	int modified = 0;

	if (IN6_IS_SCOPE_LINKLOCAL(in6) || IN6_IS_ADDR_MC_INTFACELOCAL(in6)) {
		if (in6->s6_addr16[1] != 0)
			modified = 1;
		in6->s6_addr16[1] = 0;
	}

	return (modified);
}