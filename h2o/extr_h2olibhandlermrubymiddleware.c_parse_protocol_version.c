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

/* Variables and functions */
 scalar_t__ memcmp (char const*,char*,int) ; 

__attribute__((used)) static int parse_protocol_version(const char *s, size_t len)
{
    int ver;

    if (len < 6)
        goto Default;
    if (memcmp(s, "HTTP/", 5) != 0)
        goto Default;
    if (!('0' <= s[5] && s[5] <= '9'))
        goto Default;
    ver = (s[5] - '0') * 0x100;
    if (len >= 8 && s[6] == '.' && ('0' <= s[7] && s[7] <= '9'))
        ver += s[7] - '0';

    return ver;
Default:
    return 0x101;
}