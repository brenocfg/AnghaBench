#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uECC_word_t ;
struct TYPE_4__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 TYPE_1__ curve_secp224r1 ; 
 int num_words_secp224r1 ; 
 int /*<<< orphan*/  uECC_vli_modAdd (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uECC_vli_modMult_fast (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  uECC_vli_modSquare_fast (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_1__*) ; 

__attribute__((used)) static void mod_sqrt_secp224r1_rs(uECC_word_t *d1,
                                  uECC_word_t *e1,
                                  uECC_word_t *f1,
                                  const uECC_word_t *d0,
                                  const uECC_word_t *e0,
                                  const uECC_word_t *f0) {
    uECC_word_t t[num_words_secp224r1];

    uECC_vli_modSquare_fast(t, d0, &curve_secp224r1);                    /* t <-- d0 ^ 2 */
    uECC_vli_modMult_fast(e1, d0, e0, &curve_secp224r1);                 /* e1 <-- d0 * e0 */
    uECC_vli_modAdd(d1, t, f0, curve_secp224r1.p, num_words_secp224r1);  /* d1 <-- t  + f0 */
    uECC_vli_modAdd(e1, e1, e1, curve_secp224r1.p, num_words_secp224r1); /* e1 <-- e1 + e1 */
    uECC_vli_modMult_fast(f1, t, f0, &curve_secp224r1);                  /* f1 <-- t  * f0 */
    uECC_vli_modAdd(f1, f1, f1, curve_secp224r1.p, num_words_secp224r1); /* f1 <-- f1 + f1 */
    uECC_vli_modAdd(f1, f1, f1, curve_secp224r1.p, num_words_secp224r1); /* f1 <-- f1 + f1 */
}