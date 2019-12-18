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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  mults ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int secp256k1_rand32 () ; 
 int secp256k1_rand_bits (int) ; 

void test_rand_bits(int rand32, int bits) {
    /* (1-1/2^B)^rounds[B] < 1/10^9, so rounds is the number of iterations to
     * get a false negative chance below once in a billion */
    static const unsigned int rounds[7] = {1, 30, 73, 156, 322, 653, 1316};
    /* We try multiplying the results with various odd numbers, which shouldn't
     * influence the uniform distribution modulo a power of 2. */
    static const uint32_t mults[6] = {1, 3, 21, 289, 0x9999, 0x80402011};
    /* We only select up to 6 bits from the output to analyse */
    unsigned int usebits = bits > 6 ? 6 : bits;
    unsigned int maxshift = bits - usebits;
    /* For each of the maxshift+1 usebits-bit sequences inside a bits-bit
       number, track all observed outcomes, one per bit in a uint64_t. */
    uint64_t x[6][27] = {{0}};
    unsigned int i, shift, m;
    /* Multiply the output of all rand calls with the odd number m, which
       should not change the uniformity of its distribution. */
    for (i = 0; i < rounds[usebits]; i++) {
        uint32_t r = (rand32 ? secp256k1_rand32() : secp256k1_rand_bits(bits));
        CHECK((((uint64_t)r) >> bits) == 0);
        for (m = 0; m < sizeof(mults) / sizeof(mults[0]); m++) {
            uint32_t rm = r * mults[m];
            for (shift = 0; shift <= maxshift; shift++) {
                x[m][shift] |= (((uint64_t)1) << ((rm >> shift) & ((1 << usebits) - 1)));
            }
        }
    }
    for (m = 0; m < sizeof(mults) / sizeof(mults[0]); m++) {
        for (shift = 0; shift <= maxshift; shift++) {
            /* Test that the lower usebits bits of x[shift] are 1 */
            CHECK(((~x[m][shift]) << (64 - (1 << usebits))) == 0);
        }
    }
}