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
 char const* ip6addr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 char const* ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4prefix ; 

__attribute__((used)) static const char *
format_address(netdissect_options *ndo, const u_char *prefix)
{
    if(memcmp(prefix, v4prefix, 12) == 0)
        return ipaddr_string(ndo, prefix + 12);
    else
        return ip6addr_string(ndo, prefix);
}