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

/* Variables and functions */
 int IPPROTO_IP ; 
 int IPPROTO_IPV6 ; 
 int IPPROTO_SCTP ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int IPPROTO_UDPLITE ; 
 int SOL_SOCKET ; 
 char const* lookup_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sockopt ; 
 int /*<<< orphan*/  sockoptip ; 
 int /*<<< orphan*/  sockoptipv6 ; 
 int /*<<< orphan*/  sockoptsctp ; 
 int /*<<< orphan*/  sockopttcp ; 
 int /*<<< orphan*/  sockoptudp ; 
 int /*<<< orphan*/  sockoptudplite ; 

const char *
sysdecode_sockopt_name(int level, int optname)
{

	if (level == SOL_SOCKET)
		return (lookup_value(sockopt, optname));
	if (level == IPPROTO_IP)
		/* XXX: UNIX domain socket options use a level of 0 also. */
		return (lookup_value(sockoptip, optname));
	if (level == IPPROTO_IPV6)
		return (lookup_value(sockoptipv6, optname));
	if (level == IPPROTO_SCTP)
		return (lookup_value(sockoptsctp, optname));
	if (level == IPPROTO_TCP)
		return (lookup_value(sockopttcp, optname));
	if (level == IPPROTO_UDP)
		return (lookup_value(sockoptudp, optname));
	if (level == IPPROTO_UDPLITE)
		return (lookup_value(sockoptudplite, optname));
	return (NULL);
}