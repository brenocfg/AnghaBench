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
struct in6_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int in6_nigroup0 (struct ifnet*,char const*,int,struct in6_addr*,int) ; 

int
in6_nigroup_oldmcprefix(struct ifnet *ifp, const char *name, int namelen,
    struct in6_addr *in6)
{

	return (in6_nigroup0(ifp, name, namelen, in6, 1));
}