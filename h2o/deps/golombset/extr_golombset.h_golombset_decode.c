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
typedef  scalar_t__ uint64_t ;
struct st_golombset_decode_t {void const* member_0; unsigned char* member_1; int member_2; } ;

/* Variables and functions */
 scalar_t__ golombset_decode_value (struct st_golombset_decode_t*,unsigned int,scalar_t__*) ; 

__attribute__((used)) static int golombset_decode(unsigned fixed_bits, const void *buf, size_t bufsize, uint64_t *keys, size_t *num_keys)
{
    struct st_golombset_decode_t ctx = {buf, (unsigned char *)buf + bufsize, 8};
    size_t index = 0;
    uint64_t next_min = 0;

    while (1) {
        uint64_t value;
        if (golombset_decode_value(&ctx, fixed_bits, &value) != 0)
            break;
        if (index == *num_keys) {
            /* not enough space */
            return -1;
        }
        value += next_min;
        keys[index++] = value;
        next_min = value + 1;
    }
    *num_keys = index;
    return 0;
}