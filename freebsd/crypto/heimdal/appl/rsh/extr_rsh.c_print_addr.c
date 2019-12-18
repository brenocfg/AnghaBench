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
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int /*<<< orphan*/  addr_str ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 char* inet_ntop (scalar_t__,int /*<<< orphan*/ *,char*,int) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char *
print_addr (const struct sockaddr *sa)
{
    char addr_str[256];
    char *res;
    const char *as = NULL;

    if(sa->sa_family == AF_INET)
	as = inet_ntop (sa->sa_family, &((struct sockaddr_in*)sa)->sin_addr,
			addr_str, sizeof(addr_str));
#ifdef HAVE_INET6
    else if(sa->sa_family == AF_INET6)
	as = inet_ntop (sa->sa_family, &((struct sockaddr_in6*)sa)->sin6_addr,
			addr_str, sizeof(addr_str));
#endif
    if(as == NULL)
	return NULL;
    res = strdup(as);
    if (res == NULL)
	errx (1, "malloc: out of memory");
    return res;
}