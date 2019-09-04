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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ensure_socket_initialization () ; 
 int ipv6_getnameinfo (struct sockaddr const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

int mingw_getnameinfo(const struct sockaddr *sa, socklen_t salen,
		      char *host, DWORD hostlen, char *serv, DWORD servlen,
		      int flags)
{
	ensure_socket_initialization();
	return ipv6_getnameinfo(sa, salen, host, hostlen, serv, servlen, flags);
}