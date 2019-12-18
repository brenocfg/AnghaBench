#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int caplen; int len; } ;
struct ip {int dummy; } ;
struct TYPE_7__ {scalar_t__ ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int IP_V (struct ip const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int SLIP_HDRLEN ; 
 int /*<<< orphan*/  ip6_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ip_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  sliplink_print (TYPE_1__*,int /*<<< orphan*/  const*,struct ip const*,int) ; 
 int /*<<< orphan*/  tstr ; 

u_int
sl_if_print(netdissect_options *ndo,
            const struct pcap_pkthdr *h, const u_char *p)
{
	register u_int caplen = h->caplen;
	register u_int length = h->len;
	register const struct ip *ip;

	if (caplen < SLIP_HDRLEN || length < SLIP_HDRLEN) {
		ND_PRINT((ndo, "%s", tstr));
		return (caplen);
	}

	caplen -= SLIP_HDRLEN;
	length -= SLIP_HDRLEN;

	ip = (const struct ip *)(p + SLIP_HDRLEN);

	if (ndo->ndo_eflag)
		sliplink_print(ndo, p, ip, length);

	if (caplen < 1 || length < 1) {
		ND_PRINT((ndo, "%s", tstr));
		return (caplen + SLIP_HDRLEN);
	}

	switch (IP_V(ip)) {
	case 4:
	        ip_print(ndo, (const u_char *)ip, length);
		break;
	case 6:
		ip6_print(ndo, (const u_char *)ip, length);
		break;
	default:
		ND_PRINT((ndo, "ip v%d", IP_V(ip)));
	}

	return (SLIP_HDRLEN);
}