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
 int /*<<< orphan*/  ECMA_VALUE_FALSE ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int /*<<< orphan*/  ecma_invert_boolean_value (int /*<<< orphan*/ ) ; 
 int ecma_is_value_boolean (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_op_abstract_relational_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

ecma_value_t
opfunc_relation (ecma_value_t left_value, /**< left value */
                 ecma_value_t right_value, /**< right value */
                 bool left_first, /**< 'LeftFirst' flag */
                 bool is_invert) /**< is invert */
{
  JERRY_ASSERT (!ECMA_IS_VALUE_ERROR (left_value)
                && !ECMA_IS_VALUE_ERROR (right_value));

  ecma_value_t ret_value = ecma_op_abstract_relational_compare (left_value, right_value, left_first);

  if (ECMA_IS_VALUE_ERROR (ret_value))
  {
    return ret_value;
  }

  if (ecma_is_value_undefined (ret_value))
  {
    ret_value = ECMA_VALUE_FALSE;
  }
  else
  {
    JERRY_ASSERT (ecma_is_value_boolean (ret_value));

    if (is_invert)
    {
      ret_value = ecma_invert_boolean_value (ret_value);
    }
  }

  return ret_value;
}