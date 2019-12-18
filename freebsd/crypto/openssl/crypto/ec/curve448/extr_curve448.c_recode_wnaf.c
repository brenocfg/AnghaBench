#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct smvt_control {int power; int addend; } ;
typedef  int int32_t ;
typedef  TYPE_1__* curve448_scalar_t ;
struct TYPE_3__ {int* limb; } ;

/* Variables and functions */
 unsigned int C448_SCALAR_BITS ; 
 int NUMTRAILINGZEROS (int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int recode_wnaf(struct smvt_control *control,
                       /* [nbits/(table_bits + 1) + 3] */
                       const curve448_scalar_t scalar,
                       unsigned int table_bits)
{
    unsigned int table_size = C448_SCALAR_BITS / (table_bits + 1) + 3;
    int position = table_size - 1; /* at the end */
    uint64_t current = scalar->limb[0] & 0xFFFF;
    uint32_t mask = (1 << (table_bits + 1)) - 1;
    unsigned int w;
    const unsigned int B_OVER_16 = sizeof(scalar->limb[0]) / 2;
    unsigned int n, i;

    /* place the end marker */
    control[position].power = -1;
    control[position].addend = 0;
    position--;

    /*
     * PERF: Could negate scalar if it's large.  But then would need more cases
     * in the actual code that uses it, all for an expected reduction of like
     * 1/5 op. Probably not worth it.
     */

    for (w = 1; w < (C448_SCALAR_BITS - 1) / 16 + 3; w++) {
        if (w < (C448_SCALAR_BITS - 1) / 16 + 1) {
            /* Refill the 16 high bits of current */
            current += (uint32_t)((scalar->limb[w / B_OVER_16]
                       >> (16 * (w % B_OVER_16))) << 16);
        }

        while (current & 0xFFFF) {
            uint32_t pos = NUMTRAILINGZEROS((uint32_t)current);
            uint32_t odd = (uint32_t)current >> pos;
            int32_t delta = odd & mask;

            assert(position >= 0);
            if (odd & (1 << (table_bits + 1)))
                delta -= (1 << (table_bits + 1));
            current -= delta * (1 << pos);
            control[position].power = pos + 16 * (w - 1);
            control[position].addend = delta;
            position--;
        }
        current >>= 16;
    }
    assert(current == 0);

    position++;
    n = table_size - position;
    for (i = 0; i < n; i++)
        control[i] = control[i + position];

    return n - 1;
}