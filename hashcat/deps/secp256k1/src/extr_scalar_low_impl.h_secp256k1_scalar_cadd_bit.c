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
typedef  unsigned int uint32_t ;
typedef  unsigned int secp256k1_scalar ;

/* Variables and functions */
 unsigned int EXHAUSTIVE_TEST_ORDER ; 
 unsigned int UINT32_MAX ; 
 int /*<<< orphan*/  VERIFY_CHECK (int) ; 
 scalar_t__ secp256k1_scalar_check_overflow (unsigned int*) ; 

__attribute__((used)) static void secp256k1_scalar_cadd_bit(secp256k1_scalar *r, unsigned int bit, int flag) {
    if (flag && bit < 32)
        *r += ((uint32_t)1 << bit);
#ifdef VERIFY
    VERIFY_CHECK(bit < 32);
    /* Verify that adding (1 << bit) will not overflow any in-range scalar *r by overflowing the underlying uint32_t. */
    VERIFY_CHECK(((uint32_t)1 << bit) - 1 <= UINT32_MAX - EXHAUSTIVE_TEST_ORDER);
    VERIFY_CHECK(secp256k1_scalar_check_overflow(r) == 0);
#endif
}