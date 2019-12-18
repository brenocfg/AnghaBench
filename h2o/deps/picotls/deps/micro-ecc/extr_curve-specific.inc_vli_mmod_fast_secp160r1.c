#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uECC_word_t ;
struct TYPE_2__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 TYPE_1__ curve_secp160r1 ; 
 int num_words_secp160r1 ; 
 int /*<<< orphan*/  omega_mult_secp160r1 (int*,int*) ; 
 int /*<<< orphan*/  uECC_vli_add (int*,int*,int*,int) ; 
 int /*<<< orphan*/  uECC_vli_clear (int*,int) ; 
 scalar_t__ uECC_vli_cmp_unsafe (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uECC_vli_sub (int*,int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vli_mmod_fast_secp160r1(uECC_word_t *result, uECC_word_t *product) {
    uECC_word_t tmp[2 * num_words_secp160r1];
    uECC_word_t copy;
    
    uECC_vli_clear(tmp, num_words_secp160r1);
    uECC_vli_clear(tmp + num_words_secp160r1, num_words_secp160r1);

    omega_mult_secp160r1(tmp, product + num_words_secp160r1 - 1); /* (Rq, q) = q * c */
    
    product[num_words_secp160r1 - 1] &= 0xffffffff;
    copy = tmp[num_words_secp160r1 - 1];
    tmp[num_words_secp160r1 - 1] &= 0xffffffff;
    uECC_vli_add(result, product, tmp, num_words_secp160r1); /* (C, r) = r + q */
    uECC_vli_clear(product, num_words_secp160r1);
    tmp[num_words_secp160r1 - 1] = copy;
    omega_mult_secp160r1(product, tmp + num_words_secp160r1 - 1); /* Rq*c */
    uECC_vli_add(result, result, product, num_words_secp160r1); /* (C1, r) = r + Rq*c */

    while (uECC_vli_cmp_unsafe(result, curve_secp160r1.p, num_words_secp160r1) > 0) {
        uECC_vli_sub(result, result, curve_secp160r1.p, num_words_secp160r1);
    }
}