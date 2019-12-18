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
struct ip6_hdr {int /*<<< orphan*/  ip6_dst; int /*<<< orphan*/  ip6_src; } ;
struct ip {int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_src; } ;
typedef  int /*<<< orphan*/  srcaddr ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  int /*<<< orphan*/  dstaddr ;

/* Variables and functions */
 int INET6_ADDRSTRLEN ; 
 int IP_V (struct ip const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 char* ip6addr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static void
print_nfsaddr(netdissect_options *ndo,
              const u_char *bp, const char *s, const char *d)
{
	const struct ip *ip;
	const struct ip6_hdr *ip6;
	char srcaddr[INET6_ADDRSTRLEN], dstaddr[INET6_ADDRSTRLEN];

	srcaddr[0] = dstaddr[0] = '\0';
	switch (IP_V((const struct ip *)bp)) {
	case 4:
		ip = (const struct ip *)bp;
		strlcpy(srcaddr, ipaddr_string(ndo, &ip->ip_src), sizeof(srcaddr));
		strlcpy(dstaddr, ipaddr_string(ndo, &ip->ip_dst), sizeof(dstaddr));
		break;
	case 6:
		ip6 = (const struct ip6_hdr *)bp;
		strlcpy(srcaddr, ip6addr_string(ndo, &ip6->ip6_src),
		    sizeof(srcaddr));
		strlcpy(dstaddr, ip6addr_string(ndo, &ip6->ip6_dst),
		    sizeof(dstaddr));
		break;
	default:
		strlcpy(srcaddr, "?", sizeof(srcaddr));
		strlcpy(dstaddr, "?", sizeof(dstaddr));
		break;
	}

	ND_PRINT((ndo, "%s.%s > %s.%s: ", srcaddr, s, dstaddr, d));
}