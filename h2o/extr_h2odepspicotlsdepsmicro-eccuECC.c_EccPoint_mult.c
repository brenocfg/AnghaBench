#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int wordcount_t ;
typedef  int uECC_word_t ;
typedef  TYPE_1__* uECC_Curve ;
typedef  scalar_t__ bitcount_t ;
struct TYPE_8__ {int num_words; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  XYcZ_add (int*,int*,int*,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  XYcZ_addC (int*,int*,int*,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  XYcZ_initial_double (int*,int*,int*,int*,int const*,TYPE_1__*) ; 
 int /*<<< orphan*/  apply_z (int*,int*,int*,TYPE_1__*) ; 
 int uECC_MAX_WORDS ; 
 int /*<<< orphan*/  uECC_vli_modInv (int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uECC_vli_modMult_fast (int*,int*,int const*,TYPE_1__*) ; 
 int /*<<< orphan*/  uECC_vli_modSub (int*,int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uECC_vli_set (int*,int const*,int) ; 
 int /*<<< orphan*/  uECC_vli_testBit (int const*,scalar_t__) ; 

__attribute__((used)) static void EccPoint_mult(uECC_word_t * result,
                          const uECC_word_t * point,
                          const uECC_word_t * scalar,
                          const uECC_word_t * initial_Z,
                          bitcount_t num_bits,
                          uECC_Curve curve) {
    /* R0 and R1 */
    uECC_word_t Rx[2][uECC_MAX_WORDS];
    uECC_word_t Ry[2][uECC_MAX_WORDS];
    uECC_word_t z[uECC_MAX_WORDS];
    bitcount_t i;
    uECC_word_t nb;
    wordcount_t num_words = curve->num_words;

    uECC_vli_set(Rx[1], point, num_words);
    uECC_vli_set(Ry[1], point + num_words, num_words);

    XYcZ_initial_double(Rx[1], Ry[1], Rx[0], Ry[0], initial_Z, curve);

    for (i = num_bits - 2; i > 0; --i) {
        nb = !uECC_vli_testBit(scalar, i);
        XYcZ_addC(Rx[1 - nb], Ry[1 - nb], Rx[nb], Ry[nb], curve);
        XYcZ_add(Rx[nb], Ry[nb], Rx[1 - nb], Ry[1 - nb], curve);
    }

    nb = !uECC_vli_testBit(scalar, 0);
    XYcZ_addC(Rx[1 - nb], Ry[1 - nb], Rx[nb], Ry[nb], curve);

    /* Find final 1/Z value. */
    uECC_vli_modSub(z, Rx[1], Rx[0], curve->p, num_words); /* X1 - X0 */
    uECC_vli_modMult_fast(z, z, Ry[1 - nb], curve);               /* Yb * (X1 - X0) */
    uECC_vli_modMult_fast(z, z, point, curve);                    /* xP * Yb * (X1 - X0) */
    uECC_vli_modInv(z, z, curve->p, num_words);            /* 1 / (xP * Yb * (X1 - X0)) */
    /* yP / (xP * Yb * (X1 - X0)) */
    uECC_vli_modMult_fast(z, z, point + num_words, curve);
    uECC_vli_modMult_fast(z, z, Rx[1 - nb], curve); /* Xb * yP / (xP * Yb * (X1 - X0)) */
    /* End 1/Z calculation */

    XYcZ_add(Rx[nb], Ry[nb], Rx[1 - nb], Ry[1 - nb], curve);
    apply_z(Rx[0], Ry[0], z, curve);

    uECC_vli_set(result, Rx[0], num_words);
    uECC_vli_set(result + num_words, Ry[0], num_words);
}