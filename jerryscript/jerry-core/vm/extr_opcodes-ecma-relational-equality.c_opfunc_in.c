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
 int /*<<< orphan*/  ECMA_ERR_MSG (char*) ; 
 int /*<<< orphan*/  ECMA_VALUE_ERROR ; 
 scalar_t__ JERRY_UNLIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_deref_ecma_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_get_object_from_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_is_value_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_make_boolean_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_op_object_has_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_op_to_prop_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_raise_type_error (int /*<<< orphan*/ ) ; 

ecma_value_t
opfunc_in (ecma_value_t left_value, /**< left value */
           ecma_value_t right_value) /**< right value */
{
  if (!ecma_is_value_object (right_value))
  {
    return ecma_raise_type_error (ECMA_ERR_MSG ("Expected an object in 'in' check."));
  }

  ecma_string_t *property_name_p = ecma_op_to_prop_name (left_value);

  if (JERRY_UNLIKELY (property_name_p == NULL))
  {
    return ECMA_VALUE_ERROR;
  }

  ecma_object_t *right_value_obj_p = ecma_get_object_from_value (right_value);
  ecma_value_t result = ecma_make_boolean_value (ecma_op_object_has_property (right_value_obj_p,
                                                                              property_name_p));
  ecma_deref_ecma_string (property_name_p);
  return result;
}