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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ u_int ;
typedef  scalar_t__ u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
#define  DH4OPT_DNS_SERVERS 130 
#define  DH4OPT_DOMAIN_SEARCH 129 
#define  DH4OPT_NTP_SERVERS 128 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dh4opt_str ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,scalar_t__ const*) ; 
 scalar_t__* ns_nprint (int /*<<< orphan*/ *,scalar_t__ const*,scalar_t__ const*) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int
dhcpv4_print(netdissect_options *ndo,
             const u_char *cp, u_int length, int indent)
{
    u_int i, t;
    const u_char *tlv, *value;
    uint8_t type, optlen;

    i = 0;
    while (i < length) {
        if (i + 2 > length)
            return -1;
        tlv = cp + i;
        type = (uint8_t)tlv[0];
        optlen = (uint8_t)tlv[1];
        value = tlv + 2;

        ND_PRINT((ndo, "\n"));
        for (t = indent; t > 0; t--)
            ND_PRINT((ndo, "\t"));

        ND_PRINT((ndo, "%s", tok2str(dh4opt_str, "Unknown", type)));
        ND_PRINT((ndo," (%u)", optlen + 2 ));
        if (i + 2 + optlen > length)
            return -1;

        switch (type) {
        case DH4OPT_DNS_SERVERS:
        case DH4OPT_NTP_SERVERS: {
            if (optlen < 4 || optlen % 4 != 0) {
                return -1;
            }
            for (t = 0; t < optlen; t += 4)
                ND_PRINT((ndo, " %s", ipaddr_string(ndo, value + t)));
        }
            break;
        case DH4OPT_DOMAIN_SEARCH: {
            const u_char *tp = value;
            while (tp < value + optlen) {
                ND_PRINT((ndo, " "));
                if ((tp = ns_nprint(ndo, tp, value + optlen)) == NULL)
                    return -1;
            }
        }
            break;
        }

        i += 2 + optlen;
    }
    return 0;
}