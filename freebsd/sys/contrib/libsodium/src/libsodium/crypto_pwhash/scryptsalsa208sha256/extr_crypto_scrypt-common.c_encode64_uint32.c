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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/ * itoa64 ; 

__attribute__((used)) static uint8_t *
encode64_uint32(uint8_t *dst, size_t dstlen, uint32_t src, uint32_t srcbits)
{
    uint32_t bit;

    for (bit = 0; bit < srcbits; bit += 6) {
        if (dstlen < 1) {
            return NULL; /* LCOV_EXCL_LINE */
        }
        *dst++ = itoa64[src & 0x3f];
        dstlen--;
        src >>= 6;
    }
    return dst;
}