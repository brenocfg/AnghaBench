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

__attribute__((used)) static char *append_unsafe_string_apache(char *pos, const char *src, size_t len)
{
    const char *src_end = src + len;

    for (; src != src_end; ++src) {
        if (' ' <= *src && *src < 0x7d && *src != '"') {
            *pos++ = *src;
        } else {
            *pos++ = '\\';
            *pos++ = 'x';
            *pos++ = ("0123456789abcdef")[(*src >> 4) & 0xf];
            *pos++ = ("0123456789abcdef")[*src & 0xf];
        }
    }

    return pos;
}