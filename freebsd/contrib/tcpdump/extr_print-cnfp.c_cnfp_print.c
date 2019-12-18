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
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  cnfp_v1_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cnfp_v5_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cnfp_v6_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void
cnfp_print(netdissect_options *ndo, const u_char *cp)
{
	int ver;

	/*
	 * First 2 bytes are the version number.
	 */
	ND_TCHECK2(*cp, 2);
	ver = EXTRACT_16BITS(cp);
	switch (ver) {

	case 1:
		cnfp_v1_print(ndo, cp);
		break;

	case 5:
		cnfp_v5_print(ndo, cp);
		break;

	case 6:
		cnfp_v6_print(ndo, cp);
		break;

	default:
		ND_PRINT((ndo, "NetFlow v%x", ver));
		break;
	}
	return;

trunc:
	ND_PRINT((ndo, "[|cnfp]"));
	return;
}