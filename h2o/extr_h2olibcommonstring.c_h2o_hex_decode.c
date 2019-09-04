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
 int decode_hex (int /*<<< orphan*/ ) ; 

int h2o_hex_decode(void *_dst, const char *src, size_t src_len)
{
    unsigned char *dst = _dst;

    if (src_len % 2 != 0)
        return -1;
    for (; src_len != 0; src_len -= 2) {
        int hi, lo;
        if ((hi = decode_hex(*src++)) == -1 || (lo = decode_hex(*src++)) == -1)
            return -1;
        *dst++ = (hi << 4) | lo;
    }
    return 0;
}