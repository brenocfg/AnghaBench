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
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct ip {int ip_hl; int /*<<< orphan*/  ip_dst; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  Printf (char*,...) ; 
 int /*<<< orphan*/  as_lookup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ as_path ; 
 int /*<<< orphan*/  asn ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int inetname (int /*<<< orphan*/ ) ; 
 scalar_t__ nflag ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ verbose ; 

void
print(register u_char *buf, register int cc, register struct sockaddr_in *from)
{
	register struct ip *ip;
	register int hlen;
	char addr[INET_ADDRSTRLEN];

	ip = (struct ip *) buf;
	hlen = ip->ip_hl << 2;
	cc -= hlen;

	strlcpy(addr, inet_ntoa(from->sin_addr), sizeof(addr));

	if (as_path)
		Printf(" [AS%u]", as_lookup(asn, addr, AF_INET));

	if (nflag)
		Printf(" %s", addr);
	else
		Printf(" %s (%s)", inetname(from->sin_addr), addr);

	if (verbose)
		Printf(" %d bytes to %s", cc, inet_ntoa (ip->ip_dst));
}