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
typedef  int /*<<< orphan*/  zero ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct addrinfo {scalar_t__ ai_family; scalar_t__ ai_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  IN6_IS_ADDR_V4MAPPED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
allowv4mapped(int s, struct addrinfo *ai)
{
	struct sockaddr_in6 *s6;
	int zero = 0;

	if (ai->ai_family != AF_INET6)
		return 0;

	s6 = (void *)ai->ai_addr;

	if (!IN6_IS_ADDR_V4MAPPED(&s6->sin6_addr))
		return 0;
	return setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, &zero, sizeof(zero));
}