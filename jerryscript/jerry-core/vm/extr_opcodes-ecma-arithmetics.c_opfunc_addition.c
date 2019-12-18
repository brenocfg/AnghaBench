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
typedef  int /*<<< orphan*/  ecma_string_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 scalar_t__ ECMA_IS_VALUE_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_OP_TO_NUMBER_FINALIZE (scalar_t__) ; 
 int /*<<< orphan*/  ECMA_OP_TO_NUMBER_TRY_CATCH (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_PREFERRED_TYPE_NO ; 
 int /*<<< orphan*/  ECMA_VALUE_EMPTY ; 
 int /*<<< orphan*/  ECMA_VALUE_ERROR ; 
 scalar_t__ JERRY_UNLIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_concat_ecma_strings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_deref_ecma_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_free_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_get_object_from_value (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_object (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_make_number_value (scalar_t__) ; 
 int /*<<< orphan*/  ecma_make_string_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_op_object_default_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_op_to_string (int /*<<< orphan*/ ) ; 
 scalar_t__ num_left ; 
 scalar_t__ num_right ; 

ecma_value_t
opfunc_addition (ecma_value_t left_value, /**< left value */
                 ecma_value_t right_value) /**< right value */
{
  bool free_left_value = false;
  bool free_right_value = false;

  if (ecma_is_value_object (left_value))
  {
    ecma_object_t *obj_p = ecma_get_object_from_value (left_value);
    left_value = ecma_op_object_default_value (obj_p, ECMA_PREFERRED_TYPE_NO);
    free_left_value = true;

    if (ECMA_IS_VALUE_ERROR (left_value))
    {
      return left_value;
    }
  }

  if (ecma_is_value_object (right_value))
  {
    ecma_object_t *obj_p = ecma_get_object_from_value (right_value);
    right_value = ecma_op_object_default_value (obj_p, ECMA_PREFERRED_TYPE_NO);
    free_right_value = true;

    if (ECMA_IS_VALUE_ERROR (right_value))
    {
      if (free_left_value)
      {
        ecma_free_value (left_value);
      }
      return right_value;
    }
  }

  ecma_value_t ret_value = ECMA_VALUE_EMPTY;

  if (ecma_is_value_string (left_value)
      || ecma_is_value_string (right_value))
  {
    ecma_string_t *string1_p = ecma_op_to_string (left_value);

    if (JERRY_UNLIKELY (string1_p == NULL))
    {
      if (free_left_value)
      {
        ecma_free_value (left_value);
      }
      if (free_right_value)
      {
        ecma_free_value (right_value);
      }
      return ECMA_VALUE_ERROR;
    }

    ecma_string_t *string2_p = ecma_op_to_string (right_value);

    if (JERRY_UNLIKELY (string2_p == NULL))
    {
      if (free_right_value)
      {
        ecma_free_value (right_value);
      }
      if (free_left_value)
      {
        ecma_free_value (left_value);
      }
      ecma_deref_ecma_string (string1_p);
      return ECMA_VALUE_ERROR;
    }

    string1_p = ecma_concat_ecma_strings (string1_p, string2_p);
    ret_value = ecma_make_string_value (string1_p);

    ecma_deref_ecma_string (string2_p);
  }
  else
  {
    ECMA_OP_TO_NUMBER_TRY_CATCH (num_left, left_value, ret_value);
    ECMA_OP_TO_NUMBER_TRY_CATCH (num_right, right_value, ret_value);

    ret_value = ecma_make_number_value (num_left + num_right);

    ECMA_OP_TO_NUMBER_FINALIZE (num_right);
    ECMA_OP_TO_NUMBER_FINALIZE (num_left);
  }

  if (free_left_value)
  {
    ecma_free_value (left_value);
  }

  if (free_right_value)
  {
    ecma_free_value (right_value);
  }

  return ret_value;
}