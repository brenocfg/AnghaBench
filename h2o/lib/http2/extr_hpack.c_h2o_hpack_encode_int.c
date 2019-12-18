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
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ encode_int_is_onebyte (int,unsigned int) ; 

uint8_t *h2o_hpack_encode_int(uint8_t *dst, int64_t value, unsigned prefix_bits)
{
    if (encode_int_is_onebyte(value, prefix_bits)) {
        *dst++ |= value;
    } else {
        /* see also: MAX_ENCODE_INT_LENGTH */
        assert(value >= 0);
        value -= (1 << prefix_bits) - 1;
        *dst++ |= (1 << prefix_bits) - 1;
        for (; value >= 128; value >>= 7) {
            *dst++ = 0x80 | value;
        }
        *dst++ = value;
    }
    return dst;
}