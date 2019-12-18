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
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_ERR_MSG (char*) ; 
 scalar_t__ ECMA_IS_VALUE_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIT_MAGIC_STRING_TO_STRING_UL ; 
 int /*<<< orphan*/  ecma_deref_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_free_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_get_object_from_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_make_object_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_op_function_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_op_is_callable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_op_object_get_by_magic_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_raise_type_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ecma_value_t
ecma_builtin_object_prototype_object_to_locale_string (ecma_object_t *obj_p) /**< this argument */
{
  /* 2. */
  ecma_value_t to_string_val = ecma_op_object_get_by_magic_id (obj_p, LIT_MAGIC_STRING_TO_STRING_UL);

  if (ECMA_IS_VALUE_ERROR (to_string_val))
  {
    return to_string_val;
  }

  /* 3. */
  if (!ecma_op_is_callable (to_string_val))
  {
    ecma_free_value (to_string_val);
    return ecma_raise_type_error (ECMA_ERR_MSG ("'toString is missing or not a function.'"));
  }

  /* 4. */
  ecma_object_t *to_string_func_obj_p = ecma_get_object_from_value (to_string_val);
  ecma_value_t ret_value = ecma_op_function_call (to_string_func_obj_p, ecma_make_object_value (obj_p), NULL, 0);

  ecma_deref_object (to_string_func_obj_p);

  return ret_value;
}