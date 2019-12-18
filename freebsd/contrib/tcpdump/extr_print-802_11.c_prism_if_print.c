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
typedef  scalar_t__ uint32_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int caplen; int len; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int PRISM_HDR_LEN ; 
 scalar_t__ WLANCAP_MAGIC_COOKIE_V1 ; 
 scalar_t__ WLANCAP_MAGIC_COOKIE_V2 ; 
 int ieee802_11_avs_radio_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 
 int ieee802_11_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tstr ; 

u_int
prism_if_print(netdissect_options *ndo,
               const struct pcap_pkthdr *h, const u_char *p)
{
	u_int caplen = h->caplen;
	u_int length = h->len;
	uint32_t msgcode;

	if (caplen < 4) {
		ND_PRINT((ndo, "%s", tstr));
		return caplen;
	}

	msgcode = EXTRACT_32BITS(p);
	if (msgcode == WLANCAP_MAGIC_COOKIE_V1 ||
	    msgcode == WLANCAP_MAGIC_COOKIE_V2)
		return ieee802_11_avs_radio_print(ndo, p, length, caplen);

	if (caplen < PRISM_HDR_LEN) {
		ND_PRINT((ndo, "%s", tstr));
		return caplen;
	}

	return PRISM_HDR_LEN + ieee802_11_print(ndo, p + PRISM_HDR_LEN,
	    length - PRISM_HDR_LEN, caplen - PRISM_HDR_LEN, 0, 0);
}