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
typedef  int wordcount_t ;
typedef  int /*<<< orphan*/  uECC_word_t ;
typedef  TYPE_1__* uECC_Curve ;
struct TYPE_6__ {int num_words; int /*<<< orphan*/  (* x_side ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*) ;int /*<<< orphan*/  p; } ;

/* Variables and functions */
 scalar_t__ EccPoint_isZero (int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int uECC_MAX_WORDS ; 
 int uECC_vli_cmp_unsafe (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ uECC_vli_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uECC_vli_modSquare_fast (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*) ; 

int uECC_valid_point(const uECC_word_t *point, uECC_Curve curve) {
    uECC_word_t tmp1[uECC_MAX_WORDS];
    uECC_word_t tmp2[uECC_MAX_WORDS];
    wordcount_t num_words = curve->num_words;

    /* The point at infinity is invalid. */
    if (EccPoint_isZero(point, curve)) {
        return 0;
    }

    /* x and y must be smaller than p. */
    if (uECC_vli_cmp_unsafe(curve->p, point, num_words) != 1 ||
            uECC_vli_cmp_unsafe(curve->p, point + num_words, num_words) != 1) {
        return 0;
    }

    uECC_vli_modSquare_fast(tmp1, point + num_words, curve);
    curve->x_side(tmp2, point, curve); /* tmp2 = x^3 + ax + b */

    /* Make sure that y^2 == x^3 + ax + b */
    return (int)(uECC_vli_equal(tmp1, tmp2, num_words));
}