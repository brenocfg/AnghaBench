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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int addrcmp(const struct sockaddr_storage *s1,
    const struct sockaddr_storage *s2)
{
	const struct sockaddr *sa1 = (const struct sockaddr*) s1;
	const struct sockaddr *sa2 = (const struct sockaddr*) s2;

	if (sa1->sa_family != sa2->sa_family)
		return sa1->sa_family - sa2->sa_family;
	if (sa1->sa_family == AF_INET)
		return memcmp(&((struct sockaddr_in *)s1)->sin_addr,
		    &((struct sockaddr_in *)s2)->sin_addr,
		    sizeof(struct in_addr));
#ifndef NO_IPV6
	if (sa1->sa_family == AF_INET6)
		return memcmp(&((struct sockaddr_in6 *)s1)->sin6_addr,
		    &((struct sockaddr_in6 *)s2)->sin6_addr,
		    sizeof(struct in6_addr));
#endif
	return 0;
}