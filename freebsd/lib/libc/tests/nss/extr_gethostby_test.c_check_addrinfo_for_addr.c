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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct addrinfo {int ai_family; int /*<<< orphan*/  ai_addrlen; scalar_t__ ai_addr; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (char const*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_addrinfo_for_addr(struct addrinfo *ai, char const *addr,
	socklen_t addrlen, int af)
{
	struct addrinfo *ai2;

	for (ai2 = ai; ai2 != NULL; ai2 = ai2->ai_next) {
		if (af != ai2->ai_family)
			continue;

		switch (af) {
		case AF_INET:
			if (memcmp(addr,
			    (void *)&((struct sockaddr_in *)ai2->ai_addr)->sin_addr,
			    MIN(addrlen, ai2->ai_addrlen)) == 0)
				return (0);
			break;
		case AF_INET6:
			if (memcmp(addr,
			    (void *)&((struct sockaddr_in6 *)ai2->ai_addr)->sin6_addr,
			    MIN(addrlen, ai2->ai_addrlen)) == 0)
				return (0);
			break;
		default:
			break;
		}
	}

	return (-1);
}