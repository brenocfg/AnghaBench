#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_8__ {scalar_t__ s_addr; } ;
struct TYPE_7__ {TYPE_3__ sin_addr; } ;
union vxlan_sockaddr {TYPE_1__ in6; TYPE_2__ in4; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct in_addr {scalar_t__ s_addr; } ;
struct in6_addr {int dummy; } ;
struct TYPE_10__ {struct in_addr sin_addr; } ;
struct TYPE_9__ {struct in6_addr sin6_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int IN6_ARE_ADDR_EQUAL (struct in6_addr const*,int /*<<< orphan*/ *) ; 
 TYPE_5__* satoconstsin (struct sockaddr const*) ; 
 TYPE_4__* satoconstsin6 (struct sockaddr const*) ; 

__attribute__((used)) static int
vxlan_sockaddr_in_equal(const union vxlan_sockaddr *vxladdr,
    const struct sockaddr *sa)
{
	int equal;

	if (sa->sa_family == AF_INET) {
		const struct in_addr *in4 = &satoconstsin(sa)->sin_addr;
		equal = in4->s_addr == vxladdr->in4.sin_addr.s_addr;
	} else if (sa->sa_family == AF_INET6) {
		const struct in6_addr *in6 = &satoconstsin6(sa)->sin6_addr;
		equal = IN6_ARE_ADDR_EQUAL(in6, &vxladdr->in6.sin6_addr);
	} else
		equal = 0;

	return (equal);
}