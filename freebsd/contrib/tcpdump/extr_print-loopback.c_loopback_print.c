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
 int EXTRACT_LE_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  loopback_message_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int const) ; 
 int /*<<< orphan*/  tstr ; 

void
loopback_print(netdissect_options *ndo, const u_char *cp, const u_int len)
{
	const u_char *ep = cp + len;
	uint16_t skipCount;

	ND_PRINT((ndo, "Loopback"));
	if (len < 2)
		goto invalid;
	/* skipCount */
	ND_TCHECK2(*cp, 2);
	skipCount = EXTRACT_LE_16BITS(cp);
	cp += 2;
	ND_PRINT((ndo, ", skipCount %u", skipCount));
	if (skipCount % 8)
		ND_PRINT((ndo, " (bogus)"));
	if (skipCount > len - 2)
		goto invalid;
	loopback_message_print(ndo, cp + skipCount, len - 2 - skipCount);
	return;

invalid:
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp, ep - cp);
	return;
trunc:
	ND_PRINT((ndo, "%s", tstr));
}