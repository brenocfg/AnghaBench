#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_9__ {int /*<<< orphan*/  ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int AOEV1_CMD_ISSUE_ATA_COMMAND ; 
 int AOEV1_CMD_MAC_MASK_LIST ; 
 int AOEV1_CMD_QUERY_CONFIG_INFORMATION ; 
 int AOEV1_CMD_RESERVE_RELEASE ; 
 int const AOEV1_COMMON_HDR_LEN ; 
 int AOEV1_FLAG_E ; 
 int /*<<< orphan*/  EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  aoev1_errcode_str ; 
 int /*<<< orphan*/  aoev1_flag_str ; 
 void aoev1_issue_print (TYPE_1__*,int const*,int const) ; 
 void aoev1_mac_print (TYPE_1__*,int const*,int const) ; 
 void aoev1_query_print (TYPE_1__*,int const*,int const) ; 
 void aoev1_reserve_print (TYPE_1__*,int const*,int const) ; 
 int /*<<< orphan*/  bittok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cmdcode_str ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
aoev1_print(netdissect_options *ndo,
            const u_char *cp, const u_int len)
{
	const u_char *ep = cp + len;
	uint8_t flags, command;
	void (*cmd_decoder)(netdissect_options *, const u_char *, const u_int);

	if (len < AOEV1_COMMON_HDR_LEN)
		goto invalid;
	/* Flags */
	flags = *cp & 0x0F;
	ND_PRINT((ndo, ", Flags: [%s]", bittok2str(aoev1_flag_str, "none", flags)));
	cp += 1;
	if (! ndo->ndo_vflag)
		return;
	/* Error */
	ND_TCHECK2(*cp, 1);
	if (flags & AOEV1_FLAG_E)
		ND_PRINT((ndo, "\n\tError: %s", tok2str(aoev1_errcode_str, "Invalid (%u)", *cp)));
	cp += 1;
	/* Major */
	ND_TCHECK2(*cp, 2);
	ND_PRINT((ndo, "\n\tMajor: 0x%04x", EXTRACT_16BITS(cp)));
	cp += 2;
	/* Minor */
	ND_TCHECK2(*cp, 1);
	ND_PRINT((ndo, ", Minor: 0x%02x", *cp));
	cp += 1;
	/* Command */
	ND_TCHECK2(*cp, 1);
	command = *cp;
	cp += 1;
	ND_PRINT((ndo, ", Command: %s", tok2str(cmdcode_str, "Unknown (0x%02x)", command)));
	/* Tag */
	ND_TCHECK2(*cp, 4);
	ND_PRINT((ndo, ", Tag: 0x%08x", EXTRACT_32BITS(cp)));
	cp += 4;
	/* Arg */
	cmd_decoder =
		command == AOEV1_CMD_ISSUE_ATA_COMMAND        ? aoev1_issue_print :
		command == AOEV1_CMD_QUERY_CONFIG_INFORMATION ? aoev1_query_print :
		command == AOEV1_CMD_MAC_MASK_LIST            ? aoev1_mac_print :
		command == AOEV1_CMD_RESERVE_RELEASE          ? aoev1_reserve_print :
		NULL;
	if (cmd_decoder != NULL)
		cmd_decoder(ndo, cp, len - AOEV1_COMMON_HDR_LEN);
	return;

invalid:
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp, ep - cp);
	return;
trunc:
	ND_PRINT((ndo, "%s", tstr));
}