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
 int /*<<< orphan*/  ipv4_from_asc (unsigned char*,char const*) ; 
 int /*<<< orphan*/  ipv6_from_asc (unsigned char*,char const*) ; 
 scalar_t__ strchr (char const*,char) ; 

int a2i_ipadd(unsigned char *ipout, const char *ipasc)
{
    /* If string contains a ':' assume IPv6 */

    if (strchr(ipasc, ':')) {
        if (!ipv6_from_asc(ipout, ipasc))
            return 0;
        return 16;
    } else {
        if (!ipv4_from_asc(ipout, ipasc))
            return 0;
        return 4;
    }
}