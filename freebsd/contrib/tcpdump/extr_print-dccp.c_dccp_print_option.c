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
 int /*<<< orphan*/  EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/ * dccp_feature_nums ; 
 int /*<<< orphan*/  dccp_option_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static int dccp_print_option(netdissect_options *ndo, const u_char *option, u_int hlen)
{
	uint8_t optlen, i;

	ND_TCHECK(*option);

	if (*option >= 32) {
		ND_TCHECK(*(option+1));
		optlen = *(option +1);
		if (optlen < 2) {
			if (*option >= 128)
				ND_PRINT((ndo, "CCID option %u optlen too short", *option));
			else
				ND_PRINT((ndo, "%s optlen too short",
					  tok2str(dccp_option_values, "Option %u", *option)));
			return 0;
		}
	} else
		optlen = 1;

	if (hlen < optlen) {
		if (*option >= 128)
			ND_PRINT((ndo, "CCID option %u optlen goes past header length",
				  *option));
		else
			ND_PRINT((ndo, "%s optlen goes past header length",
				  tok2str(dccp_option_values, "Option %u", *option)));
		return 0;
	}
	ND_TCHECK2(*option, optlen);

	if (*option >= 128) {
		ND_PRINT((ndo, "CCID option %d", *option));
		switch (optlen) {
			case 4:
				ND_PRINT((ndo, " %u", EXTRACT_16BITS(option + 2)));
				break;
			case 6:
				ND_PRINT((ndo, " %u", EXTRACT_32BITS(option + 2)));
				break;
			default:
				break;
		}
	} else {
		ND_PRINT((ndo, "%s", tok2str(dccp_option_values, "Option %u", *option)));
		switch (*option) {
		case 32:
		case 33:
		case 34:
		case 35:
			if (optlen < 3) {
				ND_PRINT((ndo, " optlen too short"));
				return optlen;
			}
			if (*(option + 2) < 10){
				ND_PRINT((ndo, " %s", dccp_feature_nums[*(option + 2)]));
				for (i = 0; i < optlen - 3; i++)
					ND_PRINT((ndo, " %d", *(option + 3 + i)));
			}
			break;
		case 36:
			if (optlen > 2) {
				ND_PRINT((ndo, " 0x"));
				for (i = 0; i < optlen - 2; i++)
					ND_PRINT((ndo, "%02x", *(option + 2 + i)));
			}
			break;
		case 37:
			for (i = 0; i < optlen - 2; i++)
				ND_PRINT((ndo, " %d", *(option + 2 + i)));
			break;
		case 38:
			if (optlen > 2) {
				ND_PRINT((ndo, " 0x"));
				for (i = 0; i < optlen - 2; i++)
					ND_PRINT((ndo, "%02x", *(option + 2 + i)));
			}
			break;
		case 39:
			if (optlen > 2) {
				ND_PRINT((ndo, " 0x"));
				for (i = 0; i < optlen - 2; i++)
					ND_PRINT((ndo, "%02x", *(option + 2 + i)));
			}
			break;
		case 40:
			if (optlen > 2) {
				ND_PRINT((ndo, " 0x"));
				for (i = 0; i < optlen - 2; i++)
					ND_PRINT((ndo, "%02x", *(option + 2 + i)));
			}
			break;
		case 41:
			if (optlen == 4)
				ND_PRINT((ndo, " %u", EXTRACT_32BITS(option + 2)));
			else
				ND_PRINT((ndo, " optlen != 4"));
			break;
		case 42:
			if (optlen == 4)
				ND_PRINT((ndo, " %u", EXTRACT_32BITS(option + 2)));
			else
				ND_PRINT((ndo, " optlen != 4"));
			break;
		case 43:
			if (optlen == 6)
				ND_PRINT((ndo, " %u", EXTRACT_32BITS(option + 2)));
			else if (optlen == 4)
				ND_PRINT((ndo, " %u", EXTRACT_16BITS(option + 2)));
			else
				ND_PRINT((ndo, " optlen != 4 or 6"));
			break;
		case 44:
			if (optlen > 2) {
				ND_PRINT((ndo, " "));
				for (i = 0; i < optlen - 2; i++)
					ND_PRINT((ndo, "%02x", *(option + 2 + i)));
			}
			break;
		}
	}

	return optlen;
trunc:
	ND_PRINT((ndo, "%s", tstr));
	return 0;
}