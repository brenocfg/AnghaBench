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

void h2o_hex_encode(char *dst, const void *_src, size_t src_len)
{
    const unsigned char *src = _src, *src_end = src + src_len;
    for (; src != src_end; ++src) {
        *dst++ = "0123456789abcdef"[*src >> 4];
        *dst++ = "0123456789abcdef"[*src & 0xf];
    }
    *dst = '\0';
}