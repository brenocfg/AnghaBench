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
struct sockaddr_in6 {int sin6_port; void* sin6_scope_id; int /*<<< orphan*/  sin6_addr; void* sin6_flowinfo; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr_in {int sin_port; int /*<<< orphan*/  sin_zero; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct rpcap_sockaddr_in6 {int /*<<< orphan*/  scope_id; int /*<<< orphan*/  addr; int /*<<< orphan*/  flowinfo; int /*<<< orphan*/  port; } ;
struct rpcap_sockaddr_in {int /*<<< orphan*/  addr; int /*<<< orphan*/  port; } ;
struct rpcap_sockaddr {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
#define  AIX_AF_INET6 139 
#define  HPUX_AF_INET6 138 
#define  LINUX_AF_INET6 137 
#define  NEW_BSD_AF_INET6_BSD_BE 136 
#define  NEW_BSD_AF_INET6_DARWIN_BE 135 
#define  NEW_BSD_AF_INET6_FREEBSD_BE 134 
#define  NEW_BSD_AF_INET6_LE 133 
#define  NEW_BSD_AF_INET_BE 132 
#define  NEW_BSD_AF_INET_LE 131 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
#define  RPCAP_AF_INET 130 
#define  RPCAP_AF_INET6 129 
#define  SOLARIS_AF_INET6 128 
 int /*<<< orphan*/  errno ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
rpcap_deseraddr(struct rpcap_sockaddr *sockaddrin, struct sockaddr_storage **sockaddrout, char *errbuf)
{
	/* Warning: we support only AF_INET and AF_INET6 */
	switch (ntohs(sockaddrin->family))
	{
	case RPCAP_AF_INET:
	case NEW_BSD_AF_INET_BE:
	case NEW_BSD_AF_INET_LE:
		{
		struct rpcap_sockaddr_in *sockaddrin_ipv4;
		struct sockaddr_in *sockaddrout_ipv4;

		(*sockaddrout) = (struct sockaddr_storage *) malloc(sizeof(struct sockaddr_in));
		if ((*sockaddrout) == NULL)
		{
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "malloc() failed");
			return -1;
		}
		sockaddrin_ipv4 = (struct rpcap_sockaddr_in *) sockaddrin;
		sockaddrout_ipv4 = (struct sockaddr_in *) (*sockaddrout);
		sockaddrout_ipv4->sin_family = AF_INET;
		sockaddrout_ipv4->sin_port = ntohs(sockaddrin_ipv4->port);
		memcpy(&sockaddrout_ipv4->sin_addr, &sockaddrin_ipv4->addr, sizeof(sockaddrout_ipv4->sin_addr));
		memset(sockaddrout_ipv4->sin_zero, 0, sizeof(sockaddrout_ipv4->sin_zero));
		break;
		}

#ifdef AF_INET6
	case RPCAP_AF_INET6:
	case NEW_BSD_AF_INET6_BSD_BE:
	case NEW_BSD_AF_INET6_FREEBSD_BE:
	case NEW_BSD_AF_INET6_DARWIN_BE:
	case NEW_BSD_AF_INET6_LE:
	case LINUX_AF_INET6:
	case HPUX_AF_INET6:
	case AIX_AF_INET6:
	case SOLARIS_AF_INET6:
		{
		struct rpcap_sockaddr_in6 *sockaddrin_ipv6;
		struct sockaddr_in6 *sockaddrout_ipv6;

		(*sockaddrout) = (struct sockaddr_storage *) malloc(sizeof(struct sockaddr_in6));
		if ((*sockaddrout) == NULL)
		{
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "malloc() failed");
			return -1;
		}
		sockaddrin_ipv6 = (struct rpcap_sockaddr_in6 *) sockaddrin;
		sockaddrout_ipv6 = (struct sockaddr_in6 *) (*sockaddrout);
		sockaddrout_ipv6->sin6_family = AF_INET6;
		sockaddrout_ipv6->sin6_port = ntohs(sockaddrin_ipv6->port);
		sockaddrout_ipv6->sin6_flowinfo = ntohl(sockaddrin_ipv6->flowinfo);
		memcpy(&sockaddrout_ipv6->sin6_addr, &sockaddrin_ipv6->addr, sizeof(sockaddrout_ipv6->sin6_addr));
		sockaddrout_ipv6->sin6_scope_id = ntohl(sockaddrin_ipv6->scope_id);
		break;
		}
#endif

	default:
		/*
		 * It is neither AF_INET nor AF_INET6 (or, if the OS doesn't
		 * support AF_INET6, it's not AF_INET).
		 */
		*sockaddrout = NULL;
		break;
	}
	return 0;
}