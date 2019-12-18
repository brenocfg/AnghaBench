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
typedef  int /*<<< orphan*/  uint8_t ;
struct in6_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_DEFAULT_FIB ; 
 int /*<<< orphan*/  nd6_ns_output_fib (struct ifnet*,struct in6_addr const*,struct in6_addr const*,struct in6_addr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
nd6_ns_output(struct ifnet *ifp, const struct in6_addr *saddr6,
    const struct in6_addr *daddr6, const struct in6_addr *taddr6,uint8_t *nonce)
{

	nd6_ns_output_fib(ifp, saddr6, daddr6, taddr6, nonce, RT_DEFAULT_FIB);
}