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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct in6_addr {int /*<<< orphan*/  s_addr; } ;
struct addrinfo {int ai_family; int ai_flags; } ;

/* Variables and functions */
 int AI_PASSIVE ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int PF_INET ; 
 int PF_INET6 ; 
 int PF_UNSPEC ; 
 int add_one (int,int,int,struct addrinfo***,int /*<<< orphan*/ ,struct in_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const_v4 ; 
 int /*<<< orphan*/  const_v6 ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 struct in_addr in6addr_any ; 
 struct in_addr in6addr_loopback ; 

__attribute__((used)) static int
get_null (const struct addrinfo *hints,
	  int port, int protocol, int socktype,
	  struct addrinfo **res)
{
    struct in_addr v4_addr;
#ifdef HAVE_IPV6
    struct in6_addr v6_addr;
#endif
    struct addrinfo *first = NULL;
    struct addrinfo **current = &first;
    int family = PF_UNSPEC;
    int ret;

    if (hints != NULL)
	family = hints->ai_family;

    if (hints && hints->ai_flags & AI_PASSIVE) {
	v4_addr.s_addr = INADDR_ANY;
#ifdef HAVE_IPV6
	v6_addr        = in6addr_any;
#endif
    } else {
	v4_addr.s_addr = htonl(INADDR_LOOPBACK);
#ifdef HAVE_IPV6
	v6_addr        = in6addr_loopback;
#endif
    }

#ifdef HAVE_IPV6
    if (family == PF_INET6 || family == PF_UNSPEC) {
	ret = add_one (port, protocol, socktype,
		       &current, const_v6, &v6_addr, NULL);
    }
#endif
    if (family == PF_INET || family == PF_UNSPEC) {
	ret = add_one (port, protocol, socktype,
		       &current, const_v4, &v4_addr, NULL);
    }
    *res = first;
    return 0;
}