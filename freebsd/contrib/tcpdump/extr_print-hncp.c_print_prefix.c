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
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int IPV4_MAPPED_HEADING_LEN ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int decode_prefix6 (int /*<<< orphan*/ *,int const*,int,char*,int) ; 
 char* ipaddr_string (int /*<<< orphan*/ *,struct in_addr*) ; 
 scalar_t__ is_ipv4_mapped_address (int const*) ; 
 int /*<<< orphan*/  memcpy (struct in_addr*,int const*,int) ; 
 int /*<<< orphan*/  memset (struct in_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static int
print_prefix(netdissect_options *ndo, const u_char *prefix, u_int max_length)
{
    int plenbytes;
    char buf[sizeof("xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx::/128")];

    if (prefix[0] >= 96 && max_length >= IPV4_MAPPED_HEADING_LEN + 1 &&
        is_ipv4_mapped_address(&prefix[1])) {
        struct in_addr addr;
        u_int plen;

        plen = prefix[0]-96;
        if (32 < plen)
            return -1;
        max_length -= 1;

        memset(&addr, 0, sizeof(addr));
        plenbytes = (plen + 7) / 8;
        if (max_length < (u_int)plenbytes + IPV4_MAPPED_HEADING_LEN)
            return -3;
        memcpy(&addr, &prefix[1 + IPV4_MAPPED_HEADING_LEN], plenbytes);
        if (plen % 8) {
		((u_char *)&addr)[plenbytes - 1] &=
			((0xff00 >> (plen % 8)) & 0xff);
	}
	snprintf(buf, sizeof(buf), "%s/%d", ipaddr_string(ndo, &addr), plen);
        plenbytes += 1 + IPV4_MAPPED_HEADING_LEN;
    } else {
        plenbytes = decode_prefix6(ndo, prefix, max_length, buf, sizeof(buf));
    }

    ND_PRINT((ndo, "%s", buf));
    return plenbytes;
}