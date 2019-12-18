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

/* Variables and functions */
 scalar_t__ ECMA_IS_VALUE_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_OP_TO_NUMBER_FINALIZE (scalar_t__) ; 
 int /*<<< orphan*/  ECMA_OP_TO_NUMBER_TRY_CATCH (scalar_t__,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_PREFERRED_TYPE_NUMBER ; 
 int /*<<< orphan*/  ECMA_VALUE_EMPTY ; 
 int /*<<< orphan*/  ECMA_VALUE_UNDEFINED ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int ecma_compare_ecma_strings_relational (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_free_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_get_string_from_value (int /*<<< orphan*/  const) ; 
 int ecma_is_value_string (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ecma_make_boolean_value (int) ; 
 scalar_t__ ecma_number_is_infinity (scalar_t__) ; 
 scalar_t__ ecma_number_is_nan (scalar_t__) ; 
 scalar_t__ ecma_number_is_negative (scalar_t__) ; 
 scalar_t__ ecma_number_is_zero (scalar_t__) ; 
 int /*<<< orphan*/  ecma_op_to_primitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nx ; 
 scalar_t__ ny ; 

ecma_value_t
ecma_op_abstract_relational_compare (ecma_value_t x, /**< first operand */
                                     ecma_value_t y, /**< second operand */
                                     bool left_first) /**< 'LeftFirst' flag */
{
  ecma_value_t ret_value = ECMA_VALUE_EMPTY;

  /* 1., 2. */
  ecma_value_t prim_first_converted_value = ecma_op_to_primitive (x, ECMA_PREFERRED_TYPE_NUMBER);
  if (ECMA_IS_VALUE_ERROR (prim_first_converted_value))
  {
    return prim_first_converted_value;
  }

  ecma_value_t prim_second_converted_value = ecma_op_to_primitive (y, ECMA_PREFERRED_TYPE_NUMBER);
  if (ECMA_IS_VALUE_ERROR (prim_second_converted_value))
  {
    ecma_free_value (prim_first_converted_value);
    return prim_second_converted_value;
  }

  const ecma_value_t px = left_first ? prim_first_converted_value : prim_second_converted_value;
  const ecma_value_t py = left_first ? prim_second_converted_value : prim_first_converted_value;

  const bool is_px_string = ecma_is_value_string (px);
  const bool is_py_string = ecma_is_value_string (py);

  if (!(is_px_string && is_py_string))
  {
    /* 3. */

    /* a. */
    ECMA_OP_TO_NUMBER_TRY_CATCH (nx, px, ret_value);
    ECMA_OP_TO_NUMBER_TRY_CATCH (ny, py, ret_value);

    /* b. */
    if (ecma_number_is_nan (nx)
        || ecma_number_is_nan (ny))
    {
      /* c., d. */
      ret_value = ECMA_VALUE_UNDEFINED;
    }
    else
    {
      bool is_x_less_than_y = (nx < ny);

#ifndef JERRY_NDEBUG
      bool is_x_less_than_y_check;

      if (nx == ny
          || (ecma_number_is_zero (nx)
              && ecma_number_is_zero (ny)))
      {
        /* e., f., g. */
        is_x_less_than_y_check = false;
      }
      else if (ecma_number_is_infinity (nx)
               && !ecma_number_is_negative (nx))
      {
        /* h. */
        is_x_less_than_y_check = false;
      }
      else if (ecma_number_is_infinity (ny)
               && !ecma_number_is_negative (ny))
      {
        /* i. */
        is_x_less_than_y_check = true;
      }
      else if (ecma_number_is_infinity (ny)
               && ecma_number_is_negative (ny))
      {
        /* j. */
        is_x_less_than_y_check = false;
      }
      else if (ecma_number_is_infinity (nx)
               && ecma_number_is_negative (nx))
      {
        /* k. */
        is_x_less_than_y_check = true;
      }
      else
      {
        /* l. */
        JERRY_ASSERT (!ecma_number_is_nan (nx)
                      && !ecma_number_is_infinity (nx));
        JERRY_ASSERT (!ecma_number_is_nan (ny)
                      && !ecma_number_is_infinity (ny));
        JERRY_ASSERT (!(ecma_number_is_zero (nx)
                        && ecma_number_is_zero (ny)));

        if (nx < ny)
        {
          is_x_less_than_y_check = true;
        }
        else
        {
          is_x_less_than_y_check = false;
        }
      }

      JERRY_ASSERT (is_x_less_than_y_check == is_x_less_than_y);
#endif /* !JERRY_NDEBUG */

      ret_value = ecma_make_boolean_value (is_x_less_than_y);
    }

    ECMA_OP_TO_NUMBER_FINALIZE (ny);
    ECMA_OP_TO_NUMBER_FINALIZE (nx);
  }
  else
  { /* 4. */
    JERRY_ASSERT (is_px_string && is_py_string);

    ecma_string_t *str_x_p = ecma_get_string_from_value (px);
    ecma_string_t *str_y_p = ecma_get_string_from_value (py);

    bool is_px_less = ecma_compare_ecma_strings_relational (str_x_p, str_y_p);

    ret_value = ecma_make_boolean_value (is_px_less);
  }

  ecma_free_value (prim_second_converted_value);
  ecma_free_value (prim_first_converted_value);

  return ret_value;
}