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
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int const AOEV1_ISSUE_ARG_LEN ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  aoev1_aflag_str ; 
 int /*<<< orphan*/  bittok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
aoev1_issue_print(netdissect_options *ndo,
                  const u_char *cp, const u_int len)
{
	const u_char *ep = cp + len;

	if (len < AOEV1_ISSUE_ARG_LEN)
		goto invalid;
	/* AFlags */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, "\n\tAFlags: [%s]", bittok2str(aoev1_aflag_str, "none", *cp)));
	cp += 1;
	/* Err/Feature */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, ", Err/Feature: %u", *cp));
	cp += 1;
	/* Sector Count (not correlated with the length) */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, ", Sector Count: %u", *cp));
	cp += 1;
	/* Cmd/Status */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, ", Cmd/Status: %u", *cp));
	cp += 1;
	/* lba0 */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, "\n\tlba0: %u", *cp));
	cp += 1;
	/* lba1 */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, ", lba1: %u", *cp));
	cp += 1;
	/* lba2 */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, ", lba2: %u", *cp));
	cp += 1;
	/* lba3 */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, ", lba3: %u", *cp));
	cp += 1;
	/* lba4 */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, ", lba4: %u", *cp));
	cp += 1;
	/* lba5 */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, ", lba5: %u", *cp));
	cp += 1;
	/* Reserved */
	ND_TCHECK2(*cp, 2);
	cp += 2;
	/* Data */
	if (len > AOEV1_ISSUE_ARG_LEN)
		ND_PRINT((ndo, "\n\tData: %u bytes", len - AOEV1_ISSUE_ARG_LEN));
	return;

invalid:
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp, ep - cp);
	return;
trunc:
	ND_PRINT((ndo, "%s", tstr));
}