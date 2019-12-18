#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  scalar_t__ u_char ;
struct pcap_pkthdr {scalar_t__ len; scalar_t__ caplen; } ;
struct TYPE_5__ {scalar_t__ ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 scalar_t__ PPP_HDRLEN ; 
 int /*<<< orphan*/  ppp_print (TYPE_1__*,scalar_t__ const*,scalar_t__) ; 

u_int
ppp_if_print(netdissect_options *ndo,
             const struct pcap_pkthdr *h, register const u_char *p)
{
	register u_int length = h->len;
	register u_int caplen = h->caplen;

	if (caplen < PPP_HDRLEN) {
		ND_PRINT((ndo, "[|ppp]"));
		return (caplen);
	}

#if 0
	/*
	 * XXX: seems to assume that there are 2 octets prepended to an
	 * actual PPP frame. The 1st octet looks like Input/Output flag
	 * while 2nd octet is unknown, at least to me
	 * (mshindo@mshindo.net).
	 *
	 * That was what the original tcpdump code did.
	 *
	 * FreeBSD's "if_ppp.c" *does* set the first octet to 1 for outbound
	 * packets and 0 for inbound packets - but only if the
	 * protocol field has the 0x8000 bit set (i.e., it's a network
	 * control protocol); it does so before running the packet through
	 * "bpf_filter" to see if it should be discarded, and to see
	 * if we should update the time we sent the most recent packet...
	 *
	 * ...but it puts the original address field back after doing
	 * so.
	 *
	 * NetBSD's "if_ppp.c" doesn't set the first octet in that fashion.
	 *
	 * I don't know if any PPP implementation handed up to a BPF
	 * device packets with the first octet being 1 for outbound and
	 * 0 for inbound packets, so I (guy@alum.mit.edu) don't know
	 * whether that ever needs to be checked or not.
	 *
	 * Note that NetBSD has a DLT_PPP_SERIAL, which it uses for PPP,
	 * and its tcpdump appears to assume that the frame always
	 * begins with an address field and a control field, and that
	 * the address field might be 0x0f or 0x8f, for Cisco
	 * point-to-point with HDLC framing as per section 4.3.1 of RFC
	 * 1547, as well as 0xff, for PPP in HDLC-like framing as per
	 * RFC 1662.
	 *
	 * (Is the Cisco framing in question what DLT_C_HDLC, in
	 * BSD/OS, is?)
	 */
	if (ndo->ndo_eflag)
		ND_PRINT((ndo, "%c %4d %02x ", p[0] ? 'O' : 'I', length, p[1]));
#endif

	ppp_print(ndo, p, length);

	return (0);
}