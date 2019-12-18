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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {scalar_t__ len; scalar_t__ caplen; } ;
struct enchdr {int flags; int af; int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ ENC_HDRLEN ; 
 int /*<<< orphan*/  ENC_PRINT_TYPE (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_AUTH ; 
 int /*<<< orphan*/  M_CONF ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  ip_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 

u_int
enc_if_print(netdissect_options *ndo,
             const struct pcap_pkthdr *h, register const u_char *p)
{
	register u_int length = h->len;
	register u_int caplen = h->caplen;
	int flags;
	const struct enchdr *hdr;

	if (caplen < ENC_HDRLEN) {
		ND_PRINT((ndo, "[|enc]"));
		goto out;
	}

	hdr = (const struct enchdr *)p;
	flags = hdr->flags;
	if (flags == 0)
		ND_PRINT((ndo, "(unprotected): "));
	else
		ND_PRINT((ndo, "("));
	ENC_PRINT_TYPE(flags, M_AUTH, "authentic");
	ENC_PRINT_TYPE(flags, M_CONF, "confidential");
	/* ENC_PRINT_TYPE(flags, M_TUNNEL, "tunnel"); */
	ND_PRINT((ndo, "SPI 0x%08x: ", EXTRACT_32BITS(&hdr->spi)));

	length -= ENC_HDRLEN;
	caplen -= ENC_HDRLEN;
	p += ENC_HDRLEN;

	switch (hdr->af) {
	case AF_INET:
		ip_print(ndo, p, length);
		break;
#ifdef AF_INET6
	case AF_INET6:
		ip6_print(ndo, p, length);
		break;
#endif
	}

out:
	return (ENC_HDRLEN);
}