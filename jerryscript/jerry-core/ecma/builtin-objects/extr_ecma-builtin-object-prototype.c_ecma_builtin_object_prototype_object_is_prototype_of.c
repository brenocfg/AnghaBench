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
 scalar_t__ ECMA_IS_VALUE_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_deref_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_get_object_from_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_make_boolean_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_op_object_is_prototype_of (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_op_to_object (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ecma_value_t
ecma_builtin_object_prototype_object_is_prototype_of (ecma_object_t *obj_p, /**< this argument */
                                                      ecma_value_t arg) /**< routine's first argument */
{
  /* 3. Compare prototype to object */
  ecma_value_t v_obj_value = ecma_op_to_object (arg);

  if (ECMA_IS_VALUE_ERROR (v_obj_value))
  {
    return v_obj_value;
  }

  ecma_object_t *v_obj_p = ecma_get_object_from_value (v_obj_value);

  ecma_value_t ret_value = ecma_make_boolean_value (ecma_op_object_is_prototype_of (obj_p, v_obj_p));

  ecma_deref_object (v_obj_p);

  return ret_value;
}