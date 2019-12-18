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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int len; int caplen; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int ether_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

u_int
netanalyzer_transparent_if_print(netdissect_options *ndo,
                                 const struct pcap_pkthdr *h,
                                 const u_char *p)
{
	/*
	 * Fail if we don't have enough data for the Hilscher pseudo-header,
	 * preamble, and SOF.
	 */
	if (h->len < 12 || h->caplen < 12) {
		ND_PRINT((ndo, "[|netanalyzer-transparent]"));
		return (h->caplen);
	}

	/* Skip the pseudo-header, preamble, and SOF. */
	return (12 + ether_print(ndo, p + 12, h->len - 12, h->caplen - 12, NULL, NULL));
}