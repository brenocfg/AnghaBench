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
struct hostent {int /*<<< orphan*/ * h_addr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 struct hostent* gethostbyname2 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_pton (int /*<<< orphan*/ ,char*,struct in6_addr*) ; 
 int /*<<< orphan*/  memcpy (struct in6_addr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lookup_host6 (char *host, struct in6_addr *ip6addr)
{
	struct hostent *he;

	if (!inet_pton(AF_INET6, host, ip6addr)) {
		if ((he = gethostbyname2(host, AF_INET6)) == NULL)
			return(-1);
		memcpy(ip6addr, he->h_addr_list[0], sizeof( struct in6_addr));
	}
	return (0);
}