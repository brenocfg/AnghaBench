#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int dummy; } ;
struct TYPE_6__ {int sin6_len; struct in6_addr sin6_addr; scalar_t__ sin6_family; } ;
struct in_addr {int dummy; } ;
struct TYPE_5__ {int sin_len; struct in_addr sin_addr; scalar_t__ sin_family; } ;
union vxlan_sockaddr {TYPE_2__ in6; TYPE_1__ in4; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct TYPE_8__ {struct in_addr sin_addr; } ;
struct TYPE_7__ {struct in6_addr sin6_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  MPASS (int) ; 
 TYPE_4__* satoconstsin (struct sockaddr const*) ; 
 TYPE_3__* satoconstsin6 (struct sockaddr const*) ; 

__attribute__((used)) static void
vxlan_sockaddr_in_copy(union vxlan_sockaddr *vxladdr,
    const struct sockaddr *sa)
{

	MPASS(sa->sa_family == AF_INET || sa->sa_family == AF_INET6);

	if (sa->sa_family == AF_INET) {
		const struct in_addr *in4 = &satoconstsin(sa)->sin_addr;
		vxladdr->in4.sin_family = AF_INET;
		vxladdr->in4.sin_len = sizeof(struct sockaddr_in);
		vxladdr->in4.sin_addr = *in4;
	} else if (sa->sa_family == AF_INET6) {
		const struct in6_addr *in6 = &satoconstsin6(sa)->sin6_addr;
		vxladdr->in6.sin6_family = AF_INET6;
		vxladdr->in6.sin6_len = sizeof(struct sockaddr_in6);
		vxladdr->in6.sin6_addr = *in6;
	}
}