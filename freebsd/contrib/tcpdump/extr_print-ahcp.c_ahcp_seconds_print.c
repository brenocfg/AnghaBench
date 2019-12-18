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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static int
ahcp_seconds_print(netdissect_options *ndo, const u_char *cp, const u_char *ep)
{
	if (cp + 4 != ep)
		goto invalid;
	ND_TCHECK2(*cp, 4);
	ND_PRINT((ndo, ": %us", EXTRACT_32BITS(cp)));
	return 0;

invalid:
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp, ep - cp);
	return 0;
trunc:
	ND_PRINT((ndo, "%s", tstr));
	return -1;
}