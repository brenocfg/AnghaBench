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
#define  AFNUM_INET 129 
#define  AFNUM_INET6 128 
 int FALSE ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  af_values ; 
 int /*<<< orphan*/  ip6addr_string (int /*<<< orphan*/ *,int const*) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int const*) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
cfm_network_addr_print(netdissect_options *ndo,
                       register const u_char *tptr, const u_int length)
{
    u_int network_addr_type;
    u_int hexdump =  FALSE;

    /*
     * Altough AFIs are tpically 2 octects wide,
     * 802.1ab specifies that this field width
     * is only once octet
     */
    if (length < 1) {
        ND_PRINT((ndo, "\n\t  Network Address Type (invalid, no data"));
        return hexdump;
    }
    /* The calling function must make any due ND_TCHECK calls. */
    network_addr_type = *tptr;
    ND_PRINT((ndo, "\n\t  Network Address Type %s (%u)",
           tok2str(af_values, "Unknown", network_addr_type),
           network_addr_type));

    /*
     * Resolve the passed in Address.
     */
    switch(network_addr_type) {
    case AFNUM_INET:
        if (length != 1 + 4) {
            ND_PRINT((ndo, "(invalid IPv4 address length %u)", length - 1));
            hexdump = TRUE;
            break;
        }
        ND_PRINT((ndo, ", %s", ipaddr_string(ndo, tptr + 1)));
        break;

    case AFNUM_INET6:
        if (length != 1 + 16) {
            ND_PRINT((ndo, "(invalid IPv6 address length %u)", length - 1));
            hexdump = TRUE;
            break;
        }
        ND_PRINT((ndo, ", %s", ip6addr_string(ndo, tptr + 1)));
        break;

    default:
        hexdump = TRUE;
        break;
    }

    return hexdump;
}