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
typedef  int u_char ;
struct pcap_pkthdr {scalar_t__ caplen; scalar_t__ len; } ;
struct arc_linux_header {int arc_type; } ;
struct TYPE_6__ {scalar_t__ ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  ARCTYPE_ARP_OLD 130 
#define  ARCTYPE_DIAGNOSE 129 
#define  ARCTYPE_IP_OLD 128 
 scalar_t__ ARC_LINUX_HDRLEN ; 
 scalar_t__ ARC_LINUX_HDRNEWLEN ; 
 int /*<<< orphan*/  ND_DEFAULTPRINT (int const*,scalar_t__) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  arcnet_encap_print (TYPE_1__*,int,int const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  arcnet_print (TYPE_1__*,int const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u_int
arcnet_linux_if_print(netdissect_options *ndo, const struct pcap_pkthdr *h, const u_char *p)
{
	u_int caplen = h->caplen;
	u_int length = h->len;
	const struct arc_linux_header *ap;

	int archdrlen = 0;
	u_char arc_type;

	if (caplen < ARC_LINUX_HDRLEN || length < ARC_LINUX_HDRLEN) {
		ND_PRINT((ndo, "[|arcnet]"));
		return (caplen);
	}

	ap = (const struct arc_linux_header *)p;
	arc_type = ap->arc_type;

	switch (arc_type) {
	default:
		archdrlen = ARC_LINUX_HDRNEWLEN;
		if (caplen < ARC_LINUX_HDRNEWLEN || length < ARC_LINUX_HDRNEWLEN) {
			ND_PRINT((ndo, "[|arcnet]"));
			return (caplen);
		}
		break;
	case ARCTYPE_IP_OLD:
	case ARCTYPE_ARP_OLD:
	case ARCTYPE_DIAGNOSE:
		archdrlen = ARC_LINUX_HDRLEN;
		break;
	}

	if (ndo->ndo_eflag)
		arcnet_print(ndo, p, length, 0, 0, 0);

	/*
	 * Go past the ARCNET header.
	 */
	length -= archdrlen;
	caplen -= archdrlen;
	p += archdrlen;

	if (!arcnet_encap_print(ndo, arc_type, p, length, caplen))
		ND_DEFAULTPRINT(p, caplen);

	return (archdrlen);
}