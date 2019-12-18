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
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct ether_header {int /*<<< orphan*/  ether_shost; int /*<<< orphan*/  ether_type; } ;
struct ether_arp {int arp_hln; int arp_pln; int /*<<< orphan*/  arp_tha; int /*<<< orphan*/  arp_sha; int /*<<< orphan*/  arp_pro; int /*<<< orphan*/  arp_op; int /*<<< orphan*/  arp_hrd; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 scalar_t__ ETHERTYPE_IP ; 
 scalar_t__ ETHERTYPE_REVARP ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ REVARP_REQUEST ; 
 scalar_t__ bcmp (char*,char*,int) ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rarp_check(u_char *p, u_int len)
{
	struct ether_header *ep = (struct ether_header *)p;
	struct ether_arp *ap = (struct ether_arp *)(p + sizeof(*ep));

	if (len < sizeof(*ep) + sizeof(*ap)) {
		logmsg(LOG_ERR, "truncated request, got %u, expected %lu",
				len, (u_long)(sizeof(*ep) + sizeof(*ap)));
		return 0;
	}
	/*
	 * XXX This test might be better off broken out...
	 */
	if (ntohs(ep->ether_type) != ETHERTYPE_REVARP ||
	    ntohs(ap->arp_hrd) != ARPHRD_ETHER ||
	    ntohs(ap->arp_op) != REVARP_REQUEST ||
	    ntohs(ap->arp_pro) != ETHERTYPE_IP ||
	    ap->arp_hln != 6 || ap->arp_pln != 4) {
		logmsg(LOG_DEBUG, "request fails sanity check");
		return 0;
	}
	if (bcmp((char *)&ep->ether_shost, (char *)&ap->arp_sha, 6) != 0) {
		logmsg(LOG_DEBUG, "ether/arp sender address mismatch");
		return 0;
	}
	if (bcmp((char *)&ap->arp_sha, (char *)&ap->arp_tha, 6) != 0) {
		logmsg(LOG_DEBUG, "ether/arp target address mismatch");
		return 0;
	}
	return 1;
}