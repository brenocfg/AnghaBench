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
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int EXTRACT_LE_16BITS (int /*<<< orphan*/  const*) ; 
#define  LOOPBACK_FWDDATA 129 
#define  LOOPBACK_REPLY 128 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int const) ; 
 int /*<<< orphan*/  etheraddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fcode_str ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
loopback_message_print(netdissect_options *ndo, const u_char *cp, const u_int len)
{
	const u_char *ep = cp + len;
	uint16_t function;

	if (len < 2)
		goto invalid;
	/* function */
	ND_TCHECK2(*cp, 2);
	function = EXTRACT_LE_16BITS(cp);
	cp += 2;
	ND_PRINT((ndo, ", %s", tok2str(fcode_str, " invalid (%u)", function)));

	switch (function) {
		case LOOPBACK_REPLY:
			if (len < 4)
				goto invalid;
			/* receipt number */
			ND_TCHECK2(*cp, 2);
			ND_PRINT((ndo, ", receipt number %u", EXTRACT_LE_16BITS(cp)));
			cp += 2;
			/* data */
			ND_PRINT((ndo, ", data (%u octets)", len - 4));
			ND_TCHECK2(*cp, len - 4);
			break;
		case LOOPBACK_FWDDATA:
			if (len < 8)
				goto invalid;
			/* forwarding address */
			ND_TCHECK2(*cp, ETHER_ADDR_LEN);
			ND_PRINT((ndo, ", forwarding address %s", etheraddr_string(ndo, cp)));
			cp += ETHER_ADDR_LEN;
			/* data */
			ND_PRINT((ndo, ", data (%u octets)", len - 8));
			ND_TCHECK2(*cp, len - 8);
			break;
		default:
			ND_TCHECK2(*cp, len - 2);
			break;
	}
	return;

invalid:
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp, ep - cp);
	return;
trunc:
	ND_PRINT((ndo, "%s", tstr));
}