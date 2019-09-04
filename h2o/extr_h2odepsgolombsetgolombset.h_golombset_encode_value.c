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
typedef  unsigned int uint64_t ;
struct st_golombset_encode_t {int dummy; } ;

/* Variables and functions */
 scalar_t__ golombset_encode_bit (struct st_golombset_encode_t*,int) ; 
 int golombset_encode_bits (struct st_golombset_encode_t*,unsigned int,unsigned int) ; 

__attribute__((used)) static int golombset_encode_value(struct st_golombset_encode_t *ctx, unsigned fixed_bits, uint64_t value)
{
    /* emit quontient */
    uint64_t unary_bits = value >> fixed_bits;
    for (; unary_bits != 0; --unary_bits)
        if (golombset_encode_bit(ctx, 0) != 0)
            return -1;
    if (golombset_encode_bit(ctx, 1) != 0)
        return -1;
    /* emit remainder */
    return golombset_encode_bits(ctx, fixed_bits, value);
}