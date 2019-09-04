#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uECC_word_t ;
typedef  TYPE_1__* uECC_Curve ;
struct TYPE_6__ {scalar_t__ num_n_bits; int /*<<< orphan*/  G; } ;

/* Variables and functions */
 scalar_t__ EccPoint_isZero (int*,TYPE_1__*) ; 
 int /*<<< orphan*/  EccPoint_mult (int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 int regularize_k (int*,int*,int*,TYPE_1__*) ; 
 int uECC_MAX_WORDS ; 

__attribute__((used)) static uECC_word_t EccPoint_compute_public_key(uECC_word_t *result,
                                               uECC_word_t *private_key,
                                               uECC_Curve curve) {
    uECC_word_t tmp1[uECC_MAX_WORDS];
    uECC_word_t tmp2[uECC_MAX_WORDS];
    uECC_word_t *p2[2] = {tmp1, tmp2};
    uECC_word_t carry;

    /* Regularize the bitcount for the private key so that attackers cannot use a side channel
       attack to learn the number of leading zeros. */
    carry = regularize_k(private_key, tmp1, tmp2, curve);

    EccPoint_mult(result, curve->G, p2[!carry], 0, curve->num_n_bits + 1, curve);

    if (EccPoint_isZero(result, curve)) {
        return 0;
    }
    return 1;
}