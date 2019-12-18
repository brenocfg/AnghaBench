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
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int const*) ; 
#define  IPOPT_EOL 135 
#define  IPOPT_LSRR 134 
#define  IPOPT_NOP 133 
#define  IPOPT_RA 132 
#define  IPOPT_RR 131 
#define  IPOPT_SECURITY 130 
#define  IPOPT_SSRR 129 
#define  IPOPT_TS 128 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  ip_option_values ; 
 int ip_printroute (int /*<<< orphan*/ *,int const*,int) ; 
 int ip_printts (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
ip_optprint(netdissect_options *ndo,
            register const u_char *cp, u_int length)
{
	register u_int option_len;
	const char *sep = "";

	for (; length > 0; cp += option_len, length -= option_len) {
		u_int option_code;

		ND_PRINT((ndo, "%s", sep));
		sep = ",";

		ND_TCHECK(*cp);
		option_code = *cp;

		ND_PRINT((ndo, "%s",
		          tok2str(ip_option_values,"unknown %u",option_code)));

		if (option_code == IPOPT_NOP ||
                    option_code == IPOPT_EOL)
			option_len = 1;

		else {
			ND_TCHECK(cp[1]);
			option_len = cp[1];
			if (option_len < 2) {
				ND_PRINT((ndo, " [bad length %u]", option_len));
				return;
			}
		}

		if (option_len > length) {
			ND_PRINT((ndo, " [bad length %u]", option_len));
			return;
		}

		ND_TCHECK2(*cp, option_len);

		switch (option_code) {
		case IPOPT_EOL:
			return;

		case IPOPT_TS:
			if (ip_printts(ndo, cp, option_len) == -1)
				goto trunc;
			break;

		case IPOPT_RR:       /* fall through */
		case IPOPT_SSRR:
		case IPOPT_LSRR:
			if (ip_printroute(ndo, cp, option_len) == -1)
				goto trunc;
			break;

		case IPOPT_RA:
			if (option_len < 4) {
				ND_PRINT((ndo, " [bad length %u]", option_len));
				break;
			}
			ND_TCHECK(cp[3]);
			if (EXTRACT_16BITS(&cp[2]) != 0)
				ND_PRINT((ndo, " value %u", EXTRACT_16BITS(&cp[2])));
			break;

		case IPOPT_NOP:       /* nothing to print - fall through */
		case IPOPT_SECURITY:
		default:
			break;
		}
	}
	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
}