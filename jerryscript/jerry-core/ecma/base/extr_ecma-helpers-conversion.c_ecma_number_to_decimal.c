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
typedef  int /*<<< orphan*/  lit_utf8_size_t ;
typedef  int /*<<< orphan*/  lit_utf8_byte_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ ecma_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int /*<<< orphan*/  ecma_errol0_dtoa (double,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_number_is_infinity (scalar_t__) ; 
 int /*<<< orphan*/  ecma_number_is_nan (scalar_t__) ; 
 int /*<<< orphan*/  ecma_number_is_negative (scalar_t__) ; 
 int /*<<< orphan*/  ecma_number_is_zero (scalar_t__) ; 

lit_utf8_size_t
ecma_number_to_decimal (ecma_number_t num, /**< ecma-number */
                        lit_utf8_byte_t *out_digits_p, /**< [out] buffer to fill with digits */
                        int32_t *out_decimal_exp_p) /**< [out] decimal exponent */
{
  JERRY_ASSERT (!ecma_number_is_nan (num));
  JERRY_ASSERT (!ecma_number_is_zero (num));
  JERRY_ASSERT (!ecma_number_is_infinity (num));
  JERRY_ASSERT (!ecma_number_is_negative (num));

  return ecma_errol0_dtoa ((double) num, out_digits_p, out_decimal_exp_p);
}