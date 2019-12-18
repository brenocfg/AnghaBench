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
struct in6_addr {int dummy; } ;
struct in6_nbrinfo {struct in6_addr addr; int /*<<< orphan*/  ifname; } ;
typedef  int /*<<< orphan*/  nbi ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  SIOCGNBRINFO_IN6 ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  bzero (struct in6_nbrinfo*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  if_indextoname (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static struct in6_nbrinfo *
getnbrinfo(struct in6_addr *addr, int ifindex, int warning)
{
	static struct in6_nbrinfo nbi;
	int sock;

	if ((sock = socket(AF_INET6, SOCK_DGRAM, 0)) < 0)
		err(1, "socket");

	bzero(&nbi, sizeof(nbi));
	if_indextoname(ifindex, nbi.ifname);
	nbi.addr = *addr;
	if (ioctl(sock, SIOCGNBRINFO_IN6, (caddr_t)&nbi) < 0) {
		if (warning)
			warn("ioctl(SIOCGNBRINFO_IN6)");
		close(sock);
		return(NULL);
	}

	close(sock);
	return(&nbi);
}