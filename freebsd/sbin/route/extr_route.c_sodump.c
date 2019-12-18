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
struct sockaddr_dl {int dummy; } ;
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  nbuf ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_LINK 128 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 char* inet_ntop (int,int /*<<< orphan*/ *,char*,int) ; 
 char* link_ntoa (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
sodump(struct sockaddr *sa, const char *which)
{
#ifdef INET6
	char nbuf[INET6_ADDRSTRLEN];
#endif

	switch (sa->sa_family) {
	case AF_LINK:
		(void)printf("%s: link %s; ", which,
		    link_ntoa((struct sockaddr_dl *)(void *)sa));
		break;
#ifdef INET
	case AF_INET:
		(void)printf("%s: inet %s; ", which,
		    inet_ntoa(((struct sockaddr_in *)(void *)sa)->sin_addr));
		break;
#endif
#ifdef INET6
	case AF_INET6:
		(void)printf("%s: inet6 %s; ", which, inet_ntop(sa->sa_family,
		    &((struct sockaddr_in6 *)(void *)sa)->sin6_addr, nbuf,
		    sizeof(nbuf)));
		break;
#endif
	}
	(void)fflush(stdout);
}