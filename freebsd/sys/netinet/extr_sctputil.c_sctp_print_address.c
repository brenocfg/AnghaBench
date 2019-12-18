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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  SCTP_PRINTF (char*,...) ; 
 int /*<<< orphan*/  ip6_sprintf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

void
sctp_print_address(struct sockaddr *sa)
{
#ifdef INET6
	char ip6buf[INET6_ADDRSTRLEN];
#endif

	switch (sa->sa_family) {
#ifdef INET6
	case AF_INET6:
		{
			struct sockaddr_in6 *sin6;

			sin6 = (struct sockaddr_in6 *)sa;
			SCTP_PRINTF("IPv6 address: %s:port:%d scope:%u\n",
			    ip6_sprintf(ip6buf, &sin6->sin6_addr),
			    ntohs(sin6->sin6_port),
			    sin6->sin6_scope_id);
			break;
		}
#endif
#ifdef INET
	case AF_INET:
		{
			struct sockaddr_in *sin;
			unsigned char *p;

			sin = (struct sockaddr_in *)sa;
			p = (unsigned char *)&sin->sin_addr;
			SCTP_PRINTF("IPv4 address: %u.%u.%u.%u:%d\n",
			    p[0], p[1], p[2], p[3], ntohs(sin->sin_port));
			break;
		}
#endif
	default:
		SCTP_PRINTF("?\n");
		break;
	}
}