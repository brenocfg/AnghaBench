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

/* Variables and functions */
 scalar_t__ ECMA_IS_VALUE_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 scalar_t__ ecma_is_value_boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_op_abstract_equality_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ecma_value_t
opfunc_equality (ecma_value_t left_value, /**< left value */
                 ecma_value_t right_value) /**< right value */
{
  JERRY_ASSERT (!ECMA_IS_VALUE_ERROR (left_value)
                && !ECMA_IS_VALUE_ERROR (right_value));

  ecma_value_t compare_result = ecma_op_abstract_equality_compare (left_value, right_value);

  JERRY_ASSERT (ecma_is_value_boolean (compare_result)
                || ECMA_IS_VALUE_ERROR (compare_result));

  return compare_result;
}