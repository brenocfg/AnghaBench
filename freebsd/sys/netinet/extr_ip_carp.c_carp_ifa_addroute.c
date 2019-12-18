#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct ifaddr {TYPE_1__* ifa_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  ia_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  ia_addr; } ;
struct TYPE_6__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  RTF_UP ; 
 int /*<<< orphan*/  ifa_add_loopback_route (struct ifaddr*,struct sockaddr*) ; 
 TYPE_3__* ifatoia (struct ifaddr*) ; 
 TYPE_2__* ifatoia6 (struct ifaddr*) ; 
 int /*<<< orphan*/  in_addprefix (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd6_add_ifa_lle (TYPE_2__*) ; 

__attribute__((used)) static void
carp_ifa_addroute(struct ifaddr *ifa)
{

	switch (ifa->ifa_addr->sa_family) {
#ifdef INET
	case AF_INET:
		in_addprefix(ifatoia(ifa), RTF_UP);
		ifa_add_loopback_route(ifa,
		    (struct sockaddr *)&ifatoia(ifa)->ia_addr);
		break;
#endif
#ifdef INET6
	case AF_INET6:
		ifa_add_loopback_route(ifa,
		    (struct sockaddr *)&ifatoia6(ifa)->ia_addr);
		nd6_add_ifa_lle(ifatoia6(ifa));
		break;
#endif
	}
}