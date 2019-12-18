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
 int IPV4_MAPPED_HEADING_LEN ; 
 char const* ip6addr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 char const* ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ is_ipv4_mapped_address (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const char *
format_ip6addr(netdissect_options *ndo, const u_char *cp)
{
    if (is_ipv4_mapped_address(cp))
        return ipaddr_string(ndo, cp + IPV4_MAPPED_HEADING_LEN);
    else
        return ip6addr_string(ndo, cp);
}