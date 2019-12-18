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
 int /*<<< orphan*/  ecma_builtin_object_object_define_properties (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_deref_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_free_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_get_object_from_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_is_value_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_is_value_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_is_value_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_make_object_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_op_create_object_object_noarg_and_set_prototype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_raise_type_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ecma_value_t
ecma_builtin_object_object_create (ecma_value_t arg1, /**< routine's first argument */
                                   ecma_value_t arg2) /**< routine's second argument */
{
  /* 1. */
  if (!ecma_is_value_object (arg1) && !ecma_is_value_null (arg1))
  {
    return ecma_raise_type_error (ECMA_ERR_MSG ("Argument is not an object."));
  }

  ecma_object_t *obj_p = NULL;

  if (!ecma_is_value_null (arg1))
  {
    obj_p = ecma_get_object_from_value (arg1);
  }
  /* 2-3. */
  ecma_object_t *result_obj_p = ecma_op_create_object_object_noarg_and_set_prototype (obj_p);

  /* 4. */
  if (!ecma_is_value_undefined (arg2))
  {
    ecma_value_t obj = ecma_builtin_object_object_define_properties (result_obj_p, arg2);

    if (ECMA_IS_VALUE_ERROR (obj))
    {
      ecma_deref_object (result_obj_p);
      return obj;
    }

    ecma_free_value (obj);
  }

  /* 5. */
  return ecma_make_object_value (result_obj_p);
}