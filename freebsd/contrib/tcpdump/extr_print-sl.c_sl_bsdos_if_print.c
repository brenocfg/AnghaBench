#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {scalar_t__ caplen; scalar_t__ len; } ;
struct ip {int dummy; } ;
struct TYPE_6__ {scalar_t__ ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 scalar_t__ SLIP_HDRLEN ; 
 int /*<<< orphan*/  ip_print (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  sliplink_print (TYPE_1__*,int /*<<< orphan*/  const*,struct ip const*,scalar_t__) ; 
 int /*<<< orphan*/  tstr ; 

u_int
sl_bsdos_if_print(netdissect_options *ndo,
                  const struct pcap_pkthdr *h, const u_char *p)
{
	register u_int caplen = h->caplen;
	register u_int length = h->len;
	register const struct ip *ip;

	if (caplen < SLIP_HDRLEN) {
		ND_PRINT((ndo, "%s", tstr));
		return (caplen);
	}

	length -= SLIP_HDRLEN;

	ip = (const struct ip *)(p + SLIP_HDRLEN);

#ifdef notdef
	if (ndo->ndo_eflag)
		sliplink_print(ndo, p, ip, length);
#endif

	ip_print(ndo, (const u_char *)ip, length);

	return (SLIP_HDRLEN);
}