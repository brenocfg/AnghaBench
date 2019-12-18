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
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int const*) ; 
 int IP6OPT_HOMEADDR_MINLEN ; 
#define  IP6OPT_HOME_ADDRESS 132 
#define  IP6OPT_JUMBO 131 
 int IP6OPT_JUMBO_LEN ; 
 int IP6OPT_MINLEN ; 
#define  IP6OPT_PAD1 130 
#define  IP6OPT_PADN 129 
#define  IP6OPT_ROUTER_ALERT 128 
 int IP6OPT_RTALERT_LEN ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_sopt_print (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6addr_string (int /*<<< orphan*/ *,int const*) ; 

__attribute__((used)) static void
ip6_opt_print(netdissect_options *ndo, const u_char *bp, int len)
{
    int i;
    int optlen = 0;

    if (len == 0)
        return;
    for (i = 0; i < len; i += optlen) {
	if (bp[i] == IP6OPT_PAD1)
	    optlen = 1;
	else {
	    if (i + 1 < len)
		optlen = bp[i + 1] + 2;
	    else
		goto trunc;
	}
	if (i + optlen > len)
	    goto trunc;

	switch (bp[i]) {
	case IP6OPT_PAD1:
            ND_PRINT((ndo, "(pad1)"));
	    break;
	case IP6OPT_PADN:
	    if (len - i < IP6OPT_MINLEN) {
		ND_PRINT((ndo, "(padn: trunc)"));
		goto trunc;
	    }
            ND_PRINT((ndo, "(padn)"));
	    break;
	case IP6OPT_ROUTER_ALERT:
	    if (len - i < IP6OPT_RTALERT_LEN) {
		ND_PRINT((ndo, "(rtalert: trunc)"));
		goto trunc;
	    }
	    if (bp[i + 1] != IP6OPT_RTALERT_LEN - 2) {
		ND_PRINT((ndo, "(rtalert: invalid len %d)", bp[i + 1]));
		goto trunc;
	    }
	    ND_PRINT((ndo, "(rtalert: 0x%04x) ", EXTRACT_16BITS(&bp[i + 2])));
	    break;
	case IP6OPT_JUMBO:
	    if (len - i < IP6OPT_JUMBO_LEN) {
		ND_PRINT((ndo, "(jumbo: trunc)"));
		goto trunc;
	    }
	    if (bp[i + 1] != IP6OPT_JUMBO_LEN - 2) {
		ND_PRINT((ndo, "(jumbo: invalid len %d)", bp[i + 1]));
		goto trunc;
	    }
	    ND_PRINT((ndo, "(jumbo: %u) ", EXTRACT_32BITS(&bp[i + 2])));
	    break;
        case IP6OPT_HOME_ADDRESS:
	    if (len - i < IP6OPT_HOMEADDR_MINLEN) {
		ND_PRINT((ndo, "(homeaddr: trunc)"));
		goto trunc;
	    }
	    if (bp[i + 1] < IP6OPT_HOMEADDR_MINLEN - 2) {
		ND_PRINT((ndo, "(homeaddr: invalid len %d)", bp[i + 1]));
		goto trunc;
	    }
	    ND_PRINT((ndo, "(homeaddr: %s", ip6addr_string(ndo, &bp[i + 2])));
            if (bp[i + 1] > IP6OPT_HOMEADDR_MINLEN - 2) {
		ip6_sopt_print(ndo, &bp[i + IP6OPT_HOMEADDR_MINLEN],
		    (optlen - IP6OPT_HOMEADDR_MINLEN));
	    }
            ND_PRINT((ndo, ")"));
	    break;
	default:
	    if (len - i < IP6OPT_MINLEN) {
		ND_PRINT((ndo, "(type %d: trunc)", bp[i]));
		goto trunc;
	    }
	    ND_PRINT((ndo, "(opt_type 0x%02x: len=%d)", bp[i], bp[i + 1]));
	    break;
	}
    }
    ND_PRINT((ndo, " "));
    return;

trunc:
    ND_PRINT((ndo, "[trunc] "));
}