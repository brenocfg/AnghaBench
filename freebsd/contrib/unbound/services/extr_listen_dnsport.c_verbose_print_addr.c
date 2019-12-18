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
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct addrinfo {scalar_t__ ai_family; scalar_t__ ai_socktype; scalar_t__ ai_addr; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ VERB_ALGO ; 
 scalar_t__ inet_ntop (scalar_t__,void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  verbose (scalar_t__,char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static void
verbose_print_addr(struct addrinfo *addr)
{
	if(verbosity >= VERB_ALGO) {
		char buf[100];
		void* sinaddr = &((struct sockaddr_in*)addr->ai_addr)->sin_addr;
#ifdef INET6
		if(addr->ai_family == AF_INET6)
			sinaddr = &((struct sockaddr_in6*)addr->ai_addr)->
				sin6_addr;
#endif /* INET6 */
		if(inet_ntop(addr->ai_family, sinaddr, buf,
			(socklen_t)sizeof(buf)) == 0) {
			(void)strlcpy(buf, "(null)", sizeof(buf));
		}
		buf[sizeof(buf)-1] = 0;
		verbose(VERB_ALGO, "creating %s%s socket %s %d", 
			addr->ai_socktype==SOCK_DGRAM?"udp":
			addr->ai_socktype==SOCK_STREAM?"tcp":"otherproto",
			addr->ai_family==AF_INET?"4":
			addr->ai_family==AF_INET6?"6":
			"_otherfam", buf, 
			ntohs(((struct sockaddr_in*)addr->ai_addr)->sin_port));
	}
}