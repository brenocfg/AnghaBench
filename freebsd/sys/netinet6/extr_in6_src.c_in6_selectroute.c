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
struct sockaddr_in6 {int dummy; } ;
struct rtentry {int dummy; } ;
struct route_in6 {int dummy; } ;
struct ip6_pktopts {int dummy; } ;
struct ip6_moptions {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_DEFAULT_FIB ; 
 int selectroute (struct sockaddr_in6*,struct ip6_pktopts*,struct ip6_moptions*,struct route_in6*,struct ifnet**,struct rtentry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
in6_selectroute(struct sockaddr_in6 *dstsock, struct ip6_pktopts *opts,
    struct ip6_moptions *mopts, struct route_in6 *ro,
    struct ifnet **retifp, struct rtentry **retrt)
{

	return (selectroute(dstsock, opts, mopts, ro, retifp,
	    retrt, 0, RT_DEFAULT_FIB));
}