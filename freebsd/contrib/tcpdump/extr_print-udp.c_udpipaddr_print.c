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
struct ip6_hdr {scalar_t__ ip6_nxt; int /*<<< orphan*/  ip6_dst; int /*<<< orphan*/  ip6_src; } ;
struct ip {scalar_t__ ip_p; int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_src; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ IPPROTO_UDP ; 
 int IP_V (struct ip const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6addr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udpport_string (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
udpipaddr_print(netdissect_options *ndo, const struct ip *ip, int sport, int dport)
{
	const struct ip6_hdr *ip6;

	if (IP_V(ip) == 6)
		ip6 = (const struct ip6_hdr *)ip;
	else
		ip6 = NULL;

	if (ip6) {
		if (ip6->ip6_nxt == IPPROTO_UDP) {
			if (sport == -1) {
				ND_PRINT((ndo, "%s > %s: ",
					ip6addr_string(ndo, &ip6->ip6_src),
					ip6addr_string(ndo, &ip6->ip6_dst)));
			} else {
				ND_PRINT((ndo, "%s.%s > %s.%s: ",
					ip6addr_string(ndo, &ip6->ip6_src),
					udpport_string(ndo, sport),
					ip6addr_string(ndo, &ip6->ip6_dst),
					udpport_string(ndo, dport)));
			}
		} else {
			if (sport != -1) {
				ND_PRINT((ndo, "%s > %s: ",
					udpport_string(ndo, sport),
					udpport_string(ndo, dport)));
			}
		}
	} else {
		if (ip->ip_p == IPPROTO_UDP) {
			if (sport == -1) {
				ND_PRINT((ndo, "%s > %s: ",
					ipaddr_string(ndo, &ip->ip_src),
					ipaddr_string(ndo, &ip->ip_dst)));
			} else {
				ND_PRINT((ndo, "%s.%s > %s.%s: ",
					ipaddr_string(ndo, &ip->ip_src),
					udpport_string(ndo, sport),
					ipaddr_string(ndo, &ip->ip_dst),
					udpport_string(ndo, dport)));
			}
		} else {
			if (sport != -1) {
				ND_PRINT((ndo, "%s > %s: ",
					udpport_string(ndo, sport),
					udpport_string(ndo, dport)));
			}
		}
	}
}