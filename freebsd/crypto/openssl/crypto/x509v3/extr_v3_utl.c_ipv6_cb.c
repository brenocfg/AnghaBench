#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int total; int zero_pos; scalar_t__ tmp; int /*<<< orphan*/  zero_cnt; } ;
typedef  TYPE_1__ IPV6_STAT ;

/* Variables and functions */
 int /*<<< orphan*/  ipv4_from_asc (scalar_t__,char const*) ; 
 int /*<<< orphan*/  ipv6_hex (scalar_t__,char const*,int) ; 

__attribute__((used)) static int ipv6_cb(const char *elem, int len, void *usr)
{
    IPV6_STAT *s = usr;
    /* Error if 16 bytes written */
    if (s->total == 16)
        return 0;
    if (len == 0) {
        /* Zero length element, corresponds to '::' */
        if (s->zero_pos == -1)
            s->zero_pos = s->total;
        /* If we've already got a :: its an error */
        else if (s->zero_pos != s->total)
            return 0;
        s->zero_cnt++;
    } else {
        /* If more than 4 characters could be final a.b.c.d form */
        if (len > 4) {
            /* Need at least 4 bytes left */
            if (s->total > 12)
                return 0;
            /* Must be end of string */
            if (elem[len])
                return 0;
            if (!ipv4_from_asc(s->tmp + s->total, elem))
                return 0;
            s->total += 4;
        } else {
            if (!ipv6_hex(s->tmp + s->total, elem, len))
                return 0;
            s->total += 2;
        }
    }
    return 1;
}