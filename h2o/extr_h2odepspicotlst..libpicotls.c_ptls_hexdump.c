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
typedef  int uint8_t ;

/* Variables and functions */

void ptls_hexdump(char *dst, const void *_src, size_t len)
{
    const uint8_t *src = _src;
    size_t i;

    for (i = 0; i != len; ++i) {
        *dst++ = "0123456789abcdef"[src[i] >> 4];
        *dst++ = "0123456789abcdef"[src[i] & 0xf];
    }
    *dst++ = '\0';
}