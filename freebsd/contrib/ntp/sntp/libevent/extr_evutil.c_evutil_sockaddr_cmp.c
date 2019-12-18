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
struct sockaddr_in6 {scalar_t__ sin6_port; TYPE_2__ sin6_addr; } ;
struct TYPE_3__ {scalar_t__ s_addr; } ;
struct sockaddr_in {scalar_t__ sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
evutil_sockaddr_cmp(const struct sockaddr *sa1, const struct sockaddr *sa2,
    int include_port)
{
	int r;
	if (0 != (r = (sa1->sa_family - sa2->sa_family)))
		return r;

	if (sa1->sa_family == AF_INET) {
		const struct sockaddr_in *sin1, *sin2;
		sin1 = (const struct sockaddr_in *)sa1;
		sin2 = (const struct sockaddr_in *)sa2;
		if (sin1->sin_addr.s_addr < sin2->sin_addr.s_addr)
			return -1;
		else if (sin1->sin_addr.s_addr > sin2->sin_addr.s_addr)
			return 1;
		else if (include_port &&
		    (r = ((int)sin1->sin_port - (int)sin2->sin_port)))
			return r;
		else
			return 0;
	}
#ifdef AF_INET6
	else if (sa1->sa_family == AF_INET6) {
		const struct sockaddr_in6 *sin1, *sin2;
		sin1 = (const struct sockaddr_in6 *)sa1;
		sin2 = (const struct sockaddr_in6 *)sa2;
		if ((r = memcmp(sin1->sin6_addr.s6_addr, sin2->sin6_addr.s6_addr, 16)))
			return r;
		else if (include_port &&
		    (r = ((int)sin1->sin6_port - (int)sin2->sin6_port)))
			return r;
		else
			return 0;
	}
#endif
	return 1;
}