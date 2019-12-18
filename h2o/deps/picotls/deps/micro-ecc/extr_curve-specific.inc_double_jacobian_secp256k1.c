#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uECC_word_t ;
typedef  TYPE_1__* uECC_Curve ;
struct TYPE_5__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int num_words_secp256k1 ; 
 int uECC_WORD_BITS ; 
 int uECC_vli_add (int*,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uECC_vli_isZero (int*,int) ; 
 int /*<<< orphan*/  uECC_vli_modAdd (int*,int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uECC_vli_modMult_fast (int*,int*,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  uECC_vli_modSquare_fast (int*,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  uECC_vli_modSub (int*,int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uECC_vli_rshift1 (int*,int) ; 
 scalar_t__ uECC_vli_testBit (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void double_jacobian_secp256k1(uECC_word_t * X1,
                                      uECC_word_t * Y1,
                                      uECC_word_t * Z1,
                                      uECC_Curve curve) {
    /* t1 = X, t2 = Y, t3 = Z */
    uECC_word_t t4[num_words_secp256k1];
    uECC_word_t t5[num_words_secp256k1];
    
    if (uECC_vli_isZero(Z1, num_words_secp256k1)) {
        return;
    }
    
    uECC_vli_modSquare_fast(t5, Y1, curve);   /* t5 = y1^2 */
    uECC_vli_modMult_fast(t4, X1, t5, curve); /* t4 = x1*y1^2 = A */
    uECC_vli_modSquare_fast(X1, X1, curve);   /* t1 = x1^2 */
    uECC_vli_modSquare_fast(t5, t5, curve);   /* t5 = y1^4 */
    uECC_vli_modMult_fast(Z1, Y1, Z1, curve); /* t3 = y1*z1 = z3 */
    
    uECC_vli_modAdd(Y1, X1, X1, curve->p, num_words_secp256k1); /* t2 = 2*x1^2 */
    uECC_vli_modAdd(Y1, Y1, X1, curve->p, num_words_secp256k1); /* t2 = 3*x1^2 */
    if (uECC_vli_testBit(Y1, 0)) {
        uECC_word_t carry = uECC_vli_add(Y1, Y1, curve->p, num_words_secp256k1);
        uECC_vli_rshift1(Y1, num_words_secp256k1);
        Y1[num_words_secp256k1 - 1] |= carry << (uECC_WORD_BITS - 1);
    } else {
        uECC_vli_rshift1(Y1, num_words_secp256k1);
    }
    /* t2 = 3/2*(x1^2) = B */
    
    uECC_vli_modSquare_fast(X1, Y1, curve);                     /* t1 = B^2 */
    uECC_vli_modSub(X1, X1, t4, curve->p, num_words_secp256k1); /* t1 = B^2 - A */
    uECC_vli_modSub(X1, X1, t4, curve->p, num_words_secp256k1); /* t1 = B^2 - 2A = x3 */
    
    uECC_vli_modSub(t4, t4, X1, curve->p, num_words_secp256k1); /* t4 = A - x3 */
    uECC_vli_modMult_fast(Y1, Y1, t4, curve);                   /* t2 = B * (A - x3) */
    uECC_vli_modSub(Y1, Y1, t5, curve->p, num_words_secp256k1); /* t2 = B * (A - x3) - y1^4 = y3 */
}