#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int caplen; int /*<<< orphan*/  ts; } ;
struct TYPE_9__ {scalar_t__ (* ndo_if_printer ) (TYPE_1__*,struct pcap_pkthdr const*,int /*<<< orphan*/  const*) ;int ndo_Xflag; int ndo_xflag; int ndo_Aflag; int /*<<< orphan*/  const* ndo_snapend; scalar_t__ ndo_packet_number; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ascii_print (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  hex_and_ascii_print (TYPE_1__*,char*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  hex_print (TYPE_1__*,char*,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_1__*,struct pcap_pkthdr const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ts_print (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
pretty_print_packet(netdissect_options *ndo, const struct pcap_pkthdr *h,
    const u_char *sp, u_int packets_captured)
{
	u_int hdrlen;

	if(ndo->ndo_packet_number)
		ND_PRINT((ndo, "%5u  ", packets_captured));

	ts_print(ndo, &h->ts);

	/*
	 * Some printers want to check that they're not walking off the
	 * end of the packet.
	 * Rather than pass it all the way down, we set this member
	 * of the netdissect_options structure.
	 */
	ndo->ndo_snapend = sp + h->caplen;

        hdrlen = (ndo->ndo_if_printer)(ndo, h, sp);

	/*
	 * Restore the original snapend, as a printer might have
	 * changed it.
	 */
	ndo->ndo_snapend = sp + h->caplen;
	if (ndo->ndo_Xflag) {
		/*
		 * Print the raw packet data in hex and ASCII.
		 */
		if (ndo->ndo_Xflag > 1) {
			/*
			 * Include the link-layer header.
			 */
			hex_and_ascii_print(ndo, "\n\t", sp, h->caplen);
		} else {
			/*
			 * Don't include the link-layer header - and if
			 * we have nothing past the link-layer header,
			 * print nothing.
			 */
			if (h->caplen > hdrlen)
				hex_and_ascii_print(ndo, "\n\t", sp + hdrlen,
				    h->caplen - hdrlen);
		}
	} else if (ndo->ndo_xflag) {
		/*
		 * Print the raw packet data in hex.
		 */
		if (ndo->ndo_xflag > 1) {
			/*
			 * Include the link-layer header.
			 */
                        hex_print(ndo, "\n\t", sp, h->caplen);
		} else {
			/*
			 * Don't include the link-layer header - and if
			 * we have nothing past the link-layer header,
			 * print nothing.
			 */
			if (h->caplen > hdrlen)
				hex_print(ndo, "\n\t", sp + hdrlen,
                                          h->caplen - hdrlen);
		}
	} else if (ndo->ndo_Aflag) {
		/*
		 * Print the raw packet data in ASCII.
		 */
		if (ndo->ndo_Aflag > 1) {
			/*
			 * Include the link-layer header.
			 */
			ascii_print(ndo, sp, h->caplen);
		} else {
			/*
			 * Don't include the link-layer header - and if
			 * we have nothing past the link-layer header,
			 * print nothing.
			 */
			if (h->caplen > hdrlen)
				ascii_print(ndo, sp + hdrlen, h->caplen - hdrlen);
		}
	}

	ND_PRINT((ndo, "\n"));
}