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
struct st_golombset_encode_t {unsigned char* member_0; unsigned char* member_1; unsigned char* dst; } ;

/* Variables and functions */
 scalar_t__ golombset_encode_value (struct st_golombset_encode_t*,unsigned int,scalar_t__) ; 

__attribute__((used)) static int golombset_encode(unsigned fixed_bits, uint64_t *keys, size_t num_keys, void *buf, size_t *bufsize)
{
    struct st_golombset_encode_t ctx = {(unsigned char *)buf - 1, (unsigned char *)buf + *bufsize};
    size_t i;
    uint64_t next_min = 0;

    for (i = 0; i != num_keys; ++i) {
        if (golombset_encode_value(&ctx, fixed_bits, keys[i] - next_min) != 0)
            return -1;
        next_min = keys[i] + 1;
    }

    *bufsize = ctx.dst + 1 - (unsigned char *)buf;

    return 0;
}