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
typedef  int /*<<< orphan*/  ecma_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  ecma_number_calc_remainder (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_number_is_infinity (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_number_is_nan (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_number_is_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_number_make_nan () ; 

ecma_number_t
ecma_op_number_remainder (ecma_number_t left_num, /**< left operand */
                          ecma_number_t right_num) /**< right operand */
{
  if (ecma_number_is_nan (left_num)
      || ecma_number_is_nan (right_num)
      || ecma_number_is_infinity (left_num)
      || ecma_number_is_zero (right_num))
  {
    return ecma_number_make_nan ();
  }
  else if (ecma_number_is_infinity (right_num)
           || (ecma_number_is_zero (left_num)
               && !ecma_number_is_zero (right_num)))
  {
    return left_num;
  }

  return ecma_number_calc_remainder (left_num, right_num);
}