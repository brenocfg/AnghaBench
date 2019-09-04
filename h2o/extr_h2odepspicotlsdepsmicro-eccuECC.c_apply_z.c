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
typedef  int /*<<< orphan*/  const uECC_word_t ;
typedef  int /*<<< orphan*/  uECC_Curve ;

/* Variables and functions */
 int uECC_MAX_WORDS ; 
 int /*<<< orphan*/  uECC_vli_modMult_fast (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uECC_vli_modSquare_fast (int /*<<< orphan*/  const*,int /*<<< orphan*/  const* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apply_z(uECC_word_t * X1,
                    uECC_word_t * Y1,
                    const uECC_word_t * const Z,
                    uECC_Curve curve) {
    uECC_word_t t1[uECC_MAX_WORDS];

    uECC_vli_modSquare_fast(t1, Z, curve);    /* z^2 */
    uECC_vli_modMult_fast(X1, X1, t1, curve); /* x1 * z^2 */
    uECC_vli_modMult_fast(t1, t1, Z, curve);  /* z^3 */
    uECC_vli_modMult_fast(Y1, Y1, t1, curve); /* y1 * z^3 */
}