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
typedef  int uint8_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pfloghdr {scalar_t__ length; int af; } ;
struct pcap_pkthdr {int len; int caplen; } ;
struct TYPE_7__ {int /*<<< orphan*/  ndo_suppress_default_print; scalar_t__ ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  AF_INET 131 
#define  AF_INET6 130 
 int BPF_WORDALIGN (int) ; 
 scalar_t__ MIN_PFLOG_HDRLEN ; 
 int /*<<< orphan*/  ND_DEFAULTPRINT (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct pfloghdr const) ; 
#define  OPENBSD_AF_INET 129 
#define  OPENBSD_AF_INET6 128 
 int /*<<< orphan*/  ip6_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ip_print (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  pflog_print (TYPE_1__*,struct pfloghdr const*) ; 
 int /*<<< orphan*/  tstr ; 

u_int
pflog_if_print(netdissect_options *ndo, const struct pcap_pkthdr *h,
               register const u_char *p)
{
	u_int length = h->len;
	u_int hdrlen;
	u_int caplen = h->caplen;
	const struct pfloghdr *hdr;
	uint8_t af;

	/* check length */
	if (caplen < sizeof(uint8_t)) {
		ND_PRINT((ndo, "%s", tstr));
		return (caplen);
	}

#define MIN_PFLOG_HDRLEN	45
	hdr = (const struct pfloghdr *)p;
	if (hdr->length < MIN_PFLOG_HDRLEN) {
		ND_PRINT((ndo, "[pflog: invalid header length!]"));
		return (hdr->length);	/* XXX: not really */
	}
	hdrlen = BPF_WORDALIGN(hdr->length);

	if (caplen < hdrlen) {
		ND_PRINT((ndo, "%s", tstr));
		return (hdrlen);	/* XXX: true? */
	}

	/* print what we know */
	ND_TCHECK(*hdr);
	if (ndo->ndo_eflag)
		pflog_print(ndo, hdr);

	/* skip to the real packet */
	af = hdr->af;
	length -= hdrlen;
	caplen -= hdrlen;
	p += hdrlen;
	switch (af) {

		case AF_INET:
#if OPENBSD_AF_INET != AF_INET
		case OPENBSD_AF_INET:		/* XXX: read pcap files */
#endif
		        ip_print(ndo, p, length);
			break;

#if defined(AF_INET6) || defined(OPENBSD_AF_INET6)
#ifdef AF_INET6
		case AF_INET6:
#endif /* AF_INET6 */
#if !defined(AF_INET6) || OPENBSD_AF_INET6 != AF_INET6
		case OPENBSD_AF_INET6:		/* XXX: read pcap files */
#endif /* !defined(AF_INET6) || OPENBSD_AF_INET6 != AF_INET6 */
			ip6_print(ndo, p, length);
			break;
#endif /* defined(AF_INET6) || defined(OPENBSD_AF_INET6) */

	default:
		/* address family not handled, print raw packet */
		if (!ndo->ndo_eflag)
			pflog_print(ndo, hdr);
		if (!ndo->ndo_suppress_default_print)
			ND_DEFAULTPRINT(p, caplen);
	}

	return (hdrlen);
trunc:
	ND_PRINT((ndo, "%s", tstr));
	return (hdrlen);
}