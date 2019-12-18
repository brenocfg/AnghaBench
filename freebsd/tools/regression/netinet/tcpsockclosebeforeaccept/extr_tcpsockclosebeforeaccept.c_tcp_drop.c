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
struct sockaddr_in {int dummy; } ;
typedef  int /*<<< orphan*/  addrs ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (struct sockaddr_in*,struct sockaddr_storage*,int) ; 
 int sysctlbyname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sockaddr_storage*,int) ; 

__attribute__((used)) static int
tcp_drop(struct sockaddr_in *sin_local, struct sockaddr_in *sin_remote)
{
	struct sockaddr_storage addrs[2];

	/*
	 * Sysctl accepts an array of two sockaddr's, the first being the
	 * 'foreign' sockaddr, the second being the 'local' sockaddr.
	 */

	bcopy(sin_remote, &addrs[0], sizeof(*sin_remote));
	bcopy(sin_local, &addrs[1], sizeof(*sin_local));

	return (sysctlbyname("net.inet.tcp.drop", NULL, 0, addrs,
	    sizeof(addrs)));
}