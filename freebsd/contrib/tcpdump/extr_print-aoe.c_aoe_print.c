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
#define  AOE_V1 128 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  aoev1_print (int /*<<< orphan*/ *,int const*,int const) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tstr ; 

void
aoe_print(netdissect_options *ndo,
          const u_char *cp, const u_int len)
{
	const u_char *ep = cp + len;
	uint8_t ver;

	ND_PRINT((ndo, "AoE length %u", len));

	if (len < 1)
		goto invalid;
	/* Ver/Flags */
	ND_TCHECK2(*cp, 1);
	ver = (*cp & 0xF0) >> 4;
	/* Don't advance cp yet: low order 4 bits are version-specific. */
	ND_PRINT((ndo, ", Ver %u", ver));

	switch (ver) {
		case AOE_V1:
			aoev1_print(ndo, cp, len);
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