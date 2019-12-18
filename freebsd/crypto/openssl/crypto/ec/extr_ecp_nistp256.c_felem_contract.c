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
typedef  int uint128_t ;
typedef  int u64 ;
typedef  int* smallfelem ;
typedef  int /*<<< orphan*/  felem ;

/* Variables and functions */
 int /*<<< orphan*/  felem_shrink (int*,int /*<<< orphan*/  const) ; 
 int* kPrime ; 
 int /*<<< orphan*/  subtract_u64 (int*,int*,int) ; 

__attribute__((used)) static void felem_contract(smallfelem out, const felem in)
{
    unsigned i;
    u64 all_equal_so_far = 0, result = 0, carry;

    felem_shrink(out, in);
    /* small is minimal except that the value might be > p */

    all_equal_so_far--;
    /*
     * We are doing a constant time test if out >= kPrime. We need to compare
     * each u64, from most-significant to least significant. For each one, if
     * all words so far have been equal (m is all ones) then a non-equal
     * result is the answer. Otherwise we continue.
     */
    for (i = 3; i < 4; i--) {
        u64 equal;
        uint128_t a = ((uint128_t) kPrime[i]) - out[i];
        /*
         * if out[i] > kPrime[i] then a will underflow and the high 64-bits
         * will all be set.
         */
        result |= all_equal_so_far & ((u64)(a >> 64));

        /*
         * if kPrime[i] == out[i] then |equal| will be all zeros and the
         * decrement will make it all ones.
         */
        equal = kPrime[i] ^ out[i];
        equal--;
        equal &= equal << 32;
        equal &= equal << 16;
        equal &= equal << 8;
        equal &= equal << 4;
        equal &= equal << 2;
        equal &= equal << 1;
        equal = 0 - (equal >> 63);

        all_equal_so_far &= equal;
    }

    /*
     * if all_equal_so_far is still all ones then the two values are equal
     * and so out >= kPrime is true.
     */
    result |= all_equal_so_far;

    /* if out >= kPrime then we subtract kPrime. */
    subtract_u64(&out[0], &carry, result & kPrime[0]);
    subtract_u64(&out[1], &carry, carry);
    subtract_u64(&out[2], &carry, carry);
    subtract_u64(&out[3], &carry, carry);

    subtract_u64(&out[1], &carry, result & kPrime[1]);
    subtract_u64(&out[2], &carry, carry);
    subtract_u64(&out[3], &carry, carry);

    subtract_u64(&out[2], &carry, result & kPrime[2]);
    subtract_u64(&out[3], &carry, carry);

    subtract_u64(&out[3], &carry, result & kPrime[3]);
}