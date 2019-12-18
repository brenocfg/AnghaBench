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
struct hostent {int dummy; } ;
struct addrinfo {int ai_family; int ai_flags; } ;

/* Variables and functions */
 int EAI_NONAME ; 
 int PF_INET ; 
 int PF_INET6 ; 
 int PF_UNSPEC ; 
 int add_hostent (int,int,int,struct addrinfo***,int /*<<< orphan*/ ,struct hostent*,int*) ; 
 int /*<<< orphan*/  const_v4 ; 
 int /*<<< orphan*/  const_v6 ; 
 int /*<<< orphan*/  freehostent (struct hostent*) ; 
 struct hostent* getipnodebyname (char const*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
get_nodes (const char *nodename,
	   const struct addrinfo *hints,
	   int port, int protocol, int socktype,
	   struct addrinfo **res)
{
    struct addrinfo *first = NULL;
    struct addrinfo **current = &first;
    int family = PF_UNSPEC;
    int flags  = 0;
    int ret = EAI_NONAME;
    int error;

    if (hints != NULL) {
	family = hints->ai_family;
	flags  = hints->ai_flags;
    }

#ifdef HAVE_IPV6
    if (family == PF_INET6 || family == PF_UNSPEC) {
	struct hostent *he;

	he = getipnodebyname (nodename, PF_INET6, 0, &error);

	if (he != NULL) {
	    ret = add_hostent (port, protocol, socktype,
			       &current, const_v6, he, &flags);
	    freehostent (he);
	}
    }
#endif
    if (family == PF_INET || family == PF_UNSPEC) {
	struct hostent *he;

	he = getipnodebyname (nodename, PF_INET, 0, &error);

	if (he != NULL) {
	    ret = add_hostent (port, protocol, socktype,
			       &current, const_v4, he, &flags);
	    freehostent (he);
	}
    }
    *res = first;
    return ret;
}