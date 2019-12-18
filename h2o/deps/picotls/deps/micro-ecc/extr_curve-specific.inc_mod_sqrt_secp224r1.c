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
typedef  int /*<<< orphan*/  uECC_word_t ;
typedef  int /*<<< orphan*/  uECC_Curve ;
typedef  int bitcount_t ;
struct TYPE_3__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 TYPE_1__ curve_secp224r1 ; 
 int /*<<< orphan*/  mod_sqrt_secp224r1_rp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_sqrt_secp224r1_rs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int num_words_secp224r1 ; 
 scalar_t__ uECC_vli_isZero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uECC_vli_modInv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uECC_vli_modMult_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  uECC_vli_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mod_sqrt_secp224r1(uECC_word_t *a, uECC_Curve curve) {
    bitcount_t i;
    uECC_word_t e1[num_words_secp224r1];
    uECC_word_t f1[num_words_secp224r1];
    uECC_word_t d0[num_words_secp224r1];
    uECC_word_t e0[num_words_secp224r1];
    uECC_word_t f0[num_words_secp224r1];
    uECC_word_t d1[num_words_secp224r1];

    /* s = a; using constant instead of random value */
    mod_sqrt_secp224r1_rp(d0, e0, f0, a, a);           /* RP (d0, e0, f0, c, s) */
    mod_sqrt_secp224r1_rs(d1, e1, f1, d0, e0, f0);     /* RS (d1, e1, f1, d0, e0, f0) */
    for (i = 1; i <= 95; i++) {
        uECC_vli_set(d0, d1, num_words_secp224r1);          /* d0 <-- d1 */
        uECC_vli_set(e0, e1, num_words_secp224r1);          /* e0 <-- e1 */
        uECC_vli_set(f0, f1, num_words_secp224r1);          /* f0 <-- f1 */
        mod_sqrt_secp224r1_rs(d1, e1, f1, d0, e0, f0); /* RS (d1, e1, f1, d0, e0, f0) */
        if (uECC_vli_isZero(d1, num_words_secp224r1)) {     /* if d1 == 0 */
                break;
        }
    }
    uECC_vli_modInv(f1, e0, curve_secp224r1.p, num_words_secp224r1); /* f1 <-- 1 / e0 */
    uECC_vli_modMult_fast(a, d0, f1, &curve_secp224r1);              /* a  <-- d0 / e0 */
}