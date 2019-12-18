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
typedef  size_t wordcount_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uECC_word_t ;

/* Variables and functions */
 int /*<<< orphan*/  muladd (int,scalar_t__ const,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 size_t num_words_secp256k1 ; 

__attribute__((used)) static void omega_mult_secp256k1(uint64_t * result, const uint64_t * right) {
    uECC_word_t r0 = 0;
    uECC_word_t r1 = 0;
    uECC_word_t r2 = 0;
    wordcount_t k;
    
    /* Multiply by (2^32 + 2^9 + 2^8 + 2^7 + 2^6 + 2^4 + 1). */
    for (k = 0; k < num_words_secp256k1; ++k) {
        muladd(0x1000003D1ull, right[k], &r0, &r1, &r2);
        result[k] = r0;
        r0 = r1;
        r1 = r2;
        r2 = 0;
    }
    result[num_words_secp256k1] = r0;
}