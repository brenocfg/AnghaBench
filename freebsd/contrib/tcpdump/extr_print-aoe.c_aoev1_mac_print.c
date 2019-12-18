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
typedef  int uint8_t ;
typedef  int u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int const AOEV1_MAC_ARG_LEN ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  aoev1_dcmd_str ; 
 int /*<<< orphan*/  aoev1_mcmd_str ; 
 int /*<<< orphan*/  aoev1_merror_str ; 
 int /*<<< orphan*/  etheraddr_string (int /*<<< orphan*/ *,int const*) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
aoev1_mac_print(netdissect_options *ndo,
                const u_char *cp, const u_int len)
{
	const u_char *ep = cp + len;
	uint8_t dircount, i;

	if (len < AOEV1_MAC_ARG_LEN)
		goto invalid;
	/* Reserved */
	ND_TCHECK2(*cp, 1);
	cp += 1;
	/* MCmd */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, "\n\tMCmd: %s", tok2str(aoev1_mcmd_str, "Unknown (0x%02x)", *cp)));
	cp += 1;
	/* MError */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, ", MError: %s", tok2str(aoev1_merror_str, "Unknown (0x%02x)", *cp)));
	cp += 1;
	/* Dir Count */
	ND_TCHECK2(*cp, 1);
	dircount = *cp;
	cp += 1;
	ND_PRINT((ndo, ", Dir Count: %u", dircount));
	if (AOEV1_MAC_ARG_LEN + dircount * 8 > len)
		goto invalid;
	/* directives */
	for (i = 0; i < dircount; i++) {
		/* Reserved */
		ND_TCHECK2(*cp, 1);
		cp += 1;
		/* DCmd */
		ND_TCHECK2(*cp, 1);
		ND_PRINT((ndo, "\n\t DCmd: %s", tok2str(aoev1_dcmd_str, "Unknown (0x%02x)", *cp)));
		cp += 1;
		/* Ethernet Address */
		ND_TCHECK2(*cp, ETHER_ADDR_LEN);
		ND_PRINT((ndo, ", Ethernet Address: %s", etheraddr_string(ndo, cp)));
		cp += ETHER_ADDR_LEN;
	}
	return;

invalid:
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp, ep - cp);
	return;
trunc:
	ND_PRINT((ndo, "%s", tstr));
}