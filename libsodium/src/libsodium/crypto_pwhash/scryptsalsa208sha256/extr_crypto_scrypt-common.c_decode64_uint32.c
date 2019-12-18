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
 scalar_t__ decode64_one (scalar_t__*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static const uint8_t *
decode64_uint32(uint32_t *dst, uint32_t dstbits, const uint8_t *src)
{
    uint32_t bit;
    uint32_t value;

    value = 0;
    for (bit = 0; bit < dstbits; bit += 6) {
        uint32_t one;
        if (decode64_one(&one, *src)) {
            *dst = 0;
            return NULL;
        }
        src++;
        value |= one << bit;
    }
    *dst = value;

    return src;
}