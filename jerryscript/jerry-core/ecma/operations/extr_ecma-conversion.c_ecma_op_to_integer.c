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
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_number_t ;

/* Variables and functions */
 scalar_t__ ECMA_IS_VALUE_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_NUMBER_ZERO ; 
 int /*<<< orphan*/  ECMA_VALUE_EMPTY ; 
 int /*<<< orphan*/  ecma_get_number (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_number_is_infinity (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_number_is_nan (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_number_is_negative (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_number_is_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fabs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floor (int /*<<< orphan*/ ) ; 

ecma_value_t
ecma_op_to_integer (ecma_value_t value, /**< ecma value*/
                    ecma_number_t *number_p) /**< [out] ecma number */
{
  if (ECMA_IS_VALUE_ERROR (value))
  {
    return value;
  }

  /* 1 */
  ecma_value_t to_number = ecma_get_number (value, number_p);

  /* 2 */
  if (ECMA_IS_VALUE_ERROR (to_number))
  {
    return to_number;
  }

  ecma_number_t number = *number_p;

  /* 3 */
  if (ecma_number_is_nan (number))
  {
    *number_p = ECMA_NUMBER_ZERO;
    return ECMA_VALUE_EMPTY;
  }

  /* 4 */
  if (ecma_number_is_zero (number) || ecma_number_is_infinity (number))
  {
    return ECMA_VALUE_EMPTY;
  }

  ecma_number_t floor_fabs = floor (fabs (number));

  /* 5 */
  *number_p = ecma_number_is_negative (number) ? -floor_fabs : floor_fabs;
  return ECMA_VALUE_EMPTY;
}