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
typedef  int /*<<< orphan*/  u_long ;
struct sockaddr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_DEFAULT_FIB ; 
 int /*<<< orphan*/  nd6_na_output_fib (struct ifnet*,struct in6_addr const*,struct in6_addr const*,int /*<<< orphan*/ ,int,struct sockaddr*,int /*<<< orphan*/ ) ; 

void
nd6_na_output(struct ifnet *ifp, const struct in6_addr *daddr6_0,
    const struct in6_addr *taddr6, u_long flags, int tlladdr,
    struct sockaddr *sdl0)
{

	nd6_na_output_fib(ifp, daddr6_0, taddr6, flags, tlladdr, sdl0,
	    RT_DEFAULT_FIB);
}