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
typedef  int uint64_t ;
struct st_golombset_decode_t {int dummy; } ;

/* Variables and functions */
 int golombset_decode_bit (struct st_golombset_decode_t*) ; 

__attribute__((used)) static int golombset_decode_bits(struct st_golombset_decode_t *ctx, unsigned bits, uint64_t *value)
{
    int bit;

    *value = 0;
    for (; bits != 0; --bits) {
        if ((bit = golombset_decode_bit(ctx)) == -1)
            return -1;
        *value = (*value * 2) + bit;
    }

    return 0;
}