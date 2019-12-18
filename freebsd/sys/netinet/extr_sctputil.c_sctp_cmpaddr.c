#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int SCTP6_ARE_ADDR_EQUAL (struct sockaddr_in6*,struct sockaddr_in6*) ; 

int
sctp_cmpaddr(struct sockaddr *sa1, struct sockaddr *sa2)
{

	/* must be valid */
	if (sa1 == NULL || sa2 == NULL)
		return (0);

	/* must be the same family */
	if (sa1->sa_family != sa2->sa_family)
		return (0);

	switch (sa1->sa_family) {
#ifdef INET6
	case AF_INET6:
		{
			/* IPv6 addresses */
			struct sockaddr_in6 *sin6_1, *sin6_2;

			sin6_1 = (struct sockaddr_in6 *)sa1;
			sin6_2 = (struct sockaddr_in6 *)sa2;
			return (SCTP6_ARE_ADDR_EQUAL(sin6_1,
			    sin6_2));
		}
#endif
#ifdef INET
	case AF_INET:
		{
			/* IPv4 addresses */
			struct sockaddr_in *sin_1, *sin_2;

			sin_1 = (struct sockaddr_in *)sa1;
			sin_2 = (struct sockaddr_in *)sa2;
			return (sin_1->sin_addr.s_addr == sin_2->sin_addr.s_addr);
		}
#endif
	default:
		/* we don't do these... */
		return (0);
	}
}