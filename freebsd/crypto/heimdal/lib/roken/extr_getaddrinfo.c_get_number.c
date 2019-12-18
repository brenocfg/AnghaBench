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
struct in_addr {int dummy; } ;
typedef  struct in_addr in6_addr ;
struct addrinfo {int ai_family; } ;

/* Variables and functions */
 int EAI_NONAME ; 
 int PF_INET ; 
 int PF_INET6 ; 
 int PF_UNSPEC ; 
 int add_one (int,int,int,struct addrinfo***,int /*<<< orphan*/ ,struct in_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const_v4 ; 
 int /*<<< orphan*/  const_v6 ; 
 int inet_pton (int,char const*,struct in_addr*) ; 

__attribute__((used)) static int
get_number (const char *nodename,
	    const struct addrinfo *hints,
	    int port, int protocol, int socktype,
	    struct addrinfo **res)
{
    struct addrinfo *first = NULL;
    struct addrinfo **current = &first;
    int family = PF_UNSPEC;
    int ret;

    if (hints != NULL) {
	family = hints->ai_family;
    }

#ifdef HAVE_IPV6
    if (family == PF_INET6 || family == PF_UNSPEC) {
	struct in6_addr v6_addr;

	if (inet_pton (PF_INET6, nodename, &v6_addr) == 1) {
	    ret = add_one (port, protocol, socktype,
			   &current, const_v6, &v6_addr, NULL);
	    *res = first;
	    return ret;
	}
    }
#endif
    if (family == PF_INET || family == PF_UNSPEC) {
	struct in_addr v4_addr;

	if (inet_pton (PF_INET, nodename, &v4_addr) == 1) {
	    ret = add_one (port, protocol, socktype,
			   &current, const_v4, &v4_addr, NULL);
	    *res = first;
	    return ret;
	}
    }
    return EAI_NONAME;
}