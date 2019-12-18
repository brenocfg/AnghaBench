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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 TYPE_1__ curve_secp192r1 ; 
 int num_words_secp192r1 ; 
 scalar_t__ uECC_vli_add (scalar_t__*,scalar_t__*,scalar_t__*,int) ; 
 int uECC_vli_cmp_unsafe (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  uECC_vli_set (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ uECC_vli_sub (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vli_mmod_fast_secp192r1(uint64_t *result, uint64_t *product) {
    uint64_t tmp[num_words_secp192r1];
    int carry;
    
    uECC_vli_set(result, product, num_words_secp192r1);
    
    uECC_vli_set(tmp, &product[3], num_words_secp192r1);
    carry = (int)uECC_vli_add(result, result, tmp, num_words_secp192r1);
    
    tmp[0] = 0;
    tmp[1] = product[3];
    tmp[2] = product[4];
    carry += uECC_vli_add(result, result, tmp, num_words_secp192r1);
    
    tmp[0] = tmp[1] = product[5];
    tmp[2] = 0;
    carry += uECC_vli_add(result, result, tmp, num_words_secp192r1);
    
    while (carry || uECC_vli_cmp_unsafe(curve_secp192r1.p, result, num_words_secp192r1) != 1) {
        carry -= uECC_vli_sub(result, result, curve_secp192r1.p, num_words_secp192r1);
    }
}