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
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int COEF_SCALE_S ; 
 int /*<<< orphan*/  HALASSERT (int) ; 

__attribute__((used)) static inline void
ar9300_get_delta_slope_values(struct ath_hal *ah, u_int32_t coef_scaled,
    u_int32_t *coef_mantissa, u_int32_t *coef_exponent)
{
    u_int32_t coef_exp, coef_man;

    /*
     * ALGO -> coef_exp = 14-floor(log2(coef));
     * floor(log2(x)) is the highest set bit position
     */
    for (coef_exp = 31; coef_exp > 0; coef_exp--) {
        if ((coef_scaled >> coef_exp) & 0x1) {
            break;
        }
    }
    /* A coef_exp of 0 is a legal bit position but an unexpected coef_exp */
    HALASSERT(coef_exp);
    coef_exp = 14 - (coef_exp - COEF_SCALE_S);


    /*
     * ALGO -> coef_man = floor(coef* 2^coef_exp+0.5);
     * The coefficient is already shifted up for scaling
     */
    coef_man = coef_scaled + (1 << (COEF_SCALE_S - coef_exp - 1));

    *coef_mantissa = coef_man >> (COEF_SCALE_S - coef_exp);
    *coef_exponent = coef_exp - 16;
}