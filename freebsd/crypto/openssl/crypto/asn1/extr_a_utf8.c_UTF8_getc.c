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

int UTF8_getc(const unsigned char *str, int len, unsigned long *val)
{
    const unsigned char *p;
    unsigned long value;
    int ret;
    if (len <= 0)
        return 0;
    p = str;

    /* Check syntax and work out the encoded value (if correct) */
    if ((*p & 0x80) == 0) {
        value = *p++ & 0x7f;
        ret = 1;
    } else if ((*p & 0xe0) == 0xc0) {
        if (len < 2)
            return -1;
        if ((p[1] & 0xc0) != 0x80)
            return -3;
        value = (*p++ & 0x1f) << 6;
        value |= *p++ & 0x3f;
        if (value < 0x80)
            return -4;
        ret = 2;
    } else if ((*p & 0xf0) == 0xe0) {
        if (len < 3)
            return -1;
        if (((p[1] & 0xc0) != 0x80)
            || ((p[2] & 0xc0) != 0x80))
            return -3;
        value = (*p++ & 0xf) << 12;
        value |= (*p++ & 0x3f) << 6;
        value |= *p++ & 0x3f;
        if (value < 0x800)
            return -4;
        ret = 3;
    } else if ((*p & 0xf8) == 0xf0) {
        if (len < 4)
            return -1;
        if (((p[1] & 0xc0) != 0x80)
            || ((p[2] & 0xc0) != 0x80)
            || ((p[3] & 0xc0) != 0x80))
            return -3;
        value = ((unsigned long)(*p++ & 0x7)) << 18;
        value |= (*p++ & 0x3f) << 12;
        value |= (*p++ & 0x3f) << 6;
        value |= *p++ & 0x3f;
        if (value < 0x10000)
            return -4;
        ret = 4;
    } else if ((*p & 0xfc) == 0xf8) {
        if (len < 5)
            return -1;
        if (((p[1] & 0xc0) != 0x80)
            || ((p[2] & 0xc0) != 0x80)
            || ((p[3] & 0xc0) != 0x80)
            || ((p[4] & 0xc0) != 0x80))
            return -3;
        value = ((unsigned long)(*p++ & 0x3)) << 24;
        value |= ((unsigned long)(*p++ & 0x3f)) << 18;
        value |= ((unsigned long)(*p++ & 0x3f)) << 12;
        value |= (*p++ & 0x3f) << 6;
        value |= *p++ & 0x3f;
        if (value < 0x200000)
            return -4;
        ret = 5;
    } else if ((*p & 0xfe) == 0xfc) {
        if (len < 6)
            return -1;
        if (((p[1] & 0xc0) != 0x80)
            || ((p[2] & 0xc0) != 0x80)
            || ((p[3] & 0xc0) != 0x80)
            || ((p[4] & 0xc0) != 0x80)
            || ((p[5] & 0xc0) != 0x80))
            return -3;
        value = ((unsigned long)(*p++ & 0x1)) << 30;
        value |= ((unsigned long)(*p++ & 0x3f)) << 24;
        value |= ((unsigned long)(*p++ & 0x3f)) << 18;
        value |= ((unsigned long)(*p++ & 0x3f)) << 12;
        value |= (*p++ & 0x3f) << 6;
        value |= *p++ & 0x3f;
        if (value < 0x4000000)
            return -4;
        ret = 6;
    } else
        return -2;
    *val = value;
    return ret;
}