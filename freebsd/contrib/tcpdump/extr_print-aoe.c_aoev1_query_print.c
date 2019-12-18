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
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_5__ {int /*<<< orphan*/  ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int AOEV1_MAX_CONFSTR_LEN ; 
 int const AOEV1_QUERY_ARG_LEN ; 
 int EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  aoev1_ccmd_str ; 
 scalar_t__ fn_printn (TYPE_1__*,int const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
aoev1_query_print(netdissect_options *ndo,
                  const u_char *cp, const u_int len)
{
	const u_char *ep = cp + len;
	uint16_t cslen;

	if (len < AOEV1_QUERY_ARG_LEN)
		goto invalid;
	/* Buffer Count */
	ND_TCHECK2(*cp, 2);
	ND_PRINT((ndo, "\n\tBuffer Count: %u", EXTRACT_16BITS(cp)));
	cp += 2;
	/* Firmware Version */
	ND_TCHECK2(*cp, 2);
	ND_PRINT((ndo, ", Firmware Version: %u", EXTRACT_16BITS(cp)));
	cp += 2;
	/* Sector Count */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, ", Sector Count: %u", *cp));
	cp += 1;
	/* AoE/CCmd */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, ", AoE: %u, CCmd: %s", (*cp & 0xF0) >> 4,
	          tok2str(aoev1_ccmd_str, "Unknown (0x02x)", *cp & 0x0F)));
	cp += 1;
	/* Config String Length */
	ND_TCHECK2(*cp, 2);
	cslen = EXTRACT_16BITS(cp);
	cp += 2;
	if (cslen > AOEV1_MAX_CONFSTR_LEN || AOEV1_QUERY_ARG_LEN + cslen > len)
		goto invalid;
	/* Config String */
	ND_TCHECK2(*cp, cslen);
	if (cslen) {
		ND_PRINT((ndo, "\n\tConfig String (length %u): ", cslen));
		if (fn_printn(ndo, cp, cslen, ndo->ndo_snapend))
			goto trunc;
	}
	return;

invalid:
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp, ep - cp);
	return;
trunc:
	ND_PRINT((ndo, "%s", tstr));
}