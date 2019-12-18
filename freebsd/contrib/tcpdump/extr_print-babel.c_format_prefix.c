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
 char* ip6addr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 char* ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,unsigned char) ; 
 int /*<<< orphan*/  v4prefix ; 

__attribute__((used)) static const char *
format_prefix(netdissect_options *ndo, const u_char *prefix, unsigned char plen)
{
    static char buf[50];
    if(plen >= 96 && memcmp(prefix, v4prefix, 12) == 0)
        snprintf(buf, 50, "%s/%u", ipaddr_string(ndo, prefix + 12), plen - 96);
    else
        snprintf(buf, 50, "%s/%u", ip6addr_string(ndo, prefix), plen);
    buf[49] = '\0';
    return buf;
}