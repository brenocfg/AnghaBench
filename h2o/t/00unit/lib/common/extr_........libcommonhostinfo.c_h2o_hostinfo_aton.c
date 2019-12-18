#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {char* base; int len; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 char* fetch_aton_digit (char const*,char const*,unsigned char*) ; 

int h2o_hostinfo_aton(h2o_iovec_t host, struct in_addr *addr)
{
    union {
        int32_t n;
        unsigned char c[4];
    } value;
    const char *p = host.base, *end = p + host.len;
    size_t ndots = 0;

    while (1) {
        if ((p = fetch_aton_digit(p, end, value.c + ndots)) == NULL)
            return -1;
        if (ndots == 3)
            break;
        if (p == end || !(*p == '.'))
            return -1;
        ++p;
        ++ndots;
    }
    if (p != end)
        return -1;

    addr->s_addr = value.n;
    return 0;
}