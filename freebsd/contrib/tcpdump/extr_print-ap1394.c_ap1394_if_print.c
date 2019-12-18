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
typedef  int /*<<< orphan*/  u_short ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {scalar_t__ len; scalar_t__ caplen; } ;
struct lladdr_info {void* addr_string; int /*<<< orphan*/  addr; } ;
struct firewire_header {int /*<<< orphan*/  firewire_dhost; int /*<<< orphan*/  firewire_shost; int /*<<< orphan*/  firewire_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  ndo_suppress_default_print; scalar_t__ ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 scalar_t__ FIREWIRE_HDRLEN ; 
 int /*<<< orphan*/  ND_DEFAULTPRINT (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ap1394_hdr_print (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ ethertype_print (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__,scalar_t__,struct lladdr_info*,struct lladdr_info*) ; 
 void* fwaddr_string ; 

u_int
ap1394_if_print(netdissect_options *ndo, const struct pcap_pkthdr *h, const u_char *p)
{
	u_int length = h->len;
	u_int caplen = h->caplen;
	const struct firewire_header *fp;
	u_short ether_type;
	struct lladdr_info src, dst;

	if (caplen < FIREWIRE_HDRLEN) {
		ND_PRINT((ndo, "[|ap1394]"));
		return FIREWIRE_HDRLEN;
	}

	if (ndo->ndo_eflag)
		ap1394_hdr_print(ndo, p, length);

	length -= FIREWIRE_HDRLEN;
	caplen -= FIREWIRE_HDRLEN;
	fp = (const struct firewire_header *)p;
	p += FIREWIRE_HDRLEN;

	ether_type = EXTRACT_16BITS(&fp->firewire_type);
	src.addr = fp->firewire_shost;
	src.addr_string = fwaddr_string;
	dst.addr = fp->firewire_dhost;
	dst.addr_string = fwaddr_string;
	if (ethertype_print(ndo, ether_type, p, length, caplen, &src, &dst) == 0) {
		/* ether_type not known, print raw packet */
		if (!ndo->ndo_eflag)
			ap1394_hdr_print(ndo, (const u_char *)fp, length + FIREWIRE_HDRLEN);

		if (!ndo->ndo_suppress_default_print)
			ND_DEFAULTPRINT(p, caplen);
	}

	return FIREWIRE_HDRLEN;
}