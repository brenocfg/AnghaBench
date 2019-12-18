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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_string_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;
typedef  int /*<<< orphan*/  ecma_length_t ;

/* Variables and functions */
 scalar_t__ ECMA_IS_VALUE_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ECMA_OBJECT_PROTOTYPE_HAS_OWN_PROPERTY ; 
 scalar_t__ ECMA_OBJECT_PROTOTYPE_IS_PROTOTYPE_OF ; 
 scalar_t__ ECMA_OBJECT_PROTOTYPE_TO_STRING ; 
 scalar_t__ ECMA_OBJECT_PROTOTYPE_VALUE_OF ; 
 int /*<<< orphan*/  ECMA_VALUE_ERROR ; 
 int /*<<< orphan*/  ECMA_VALUE_FALSE ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int /*<<< orphan*/  JERRY_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_builtin_object_prototype_object_has_own_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_builtin_object_prototype_object_is_prototype_of (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ecma_builtin_object_prototype_object_property_is_enumerable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_builtin_object_prototype_object_to_locale_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_builtin_object_prototype_object_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_builtin_object_prototype_object_value_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_deref_ecma_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_deref_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_get_object_from_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_is_value_object (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ecma_op_to_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_op_to_prop_name (int /*<<< orphan*/  const) ; 

ecma_value_t
ecma_builtin_object_prototype_dispatch_routine (uint16_t builtin_routine_id, /**< built-in wide routine
                                                                              *   identifier */
                                                ecma_value_t this_arg, /**< 'this' argument value */
                                                const ecma_value_t arguments_list_p[], /**< list of arguments
                                                                                      *   passed to routine */
                                                ecma_length_t arguments_number) /**< length of arguments' list */
{
  JERRY_UNUSED (arguments_number);

  /* no specialization */
  if (builtin_routine_id <= ECMA_OBJECT_PROTOTYPE_VALUE_OF)
  {
    if (builtin_routine_id == ECMA_OBJECT_PROTOTYPE_TO_STRING)
    {
      return ecma_builtin_object_prototype_object_to_string (this_arg);
    }

    JERRY_ASSERT (builtin_routine_id <= ECMA_OBJECT_PROTOTYPE_VALUE_OF);

    return ecma_builtin_object_prototype_object_value_of (this_arg);
  }

  if (builtin_routine_id <= ECMA_OBJECT_PROTOTYPE_IS_PROTOTYPE_OF)
  {
    if (builtin_routine_id == ECMA_OBJECT_PROTOTYPE_IS_PROTOTYPE_OF)
    {
      /* 15.2.4.6.1. */
      if (!ecma_is_value_object (arguments_list_p[0]))
      {
        return ECMA_VALUE_FALSE;
      }
    }

    ecma_value_t to_object = ecma_op_to_object (this_arg);

    if (ECMA_IS_VALUE_ERROR (to_object))
    {
      return to_object;
    }

    ecma_object_t *obj_p = ecma_get_object_from_value (to_object);

    ecma_value_t ret_value;

    if (builtin_routine_id == ECMA_OBJECT_PROTOTYPE_IS_PROTOTYPE_OF)
    {
      ret_value = ecma_builtin_object_prototype_object_is_prototype_of (obj_p, arguments_list_p[0]);
    }
    else
    {
      ret_value = ecma_builtin_object_prototype_object_to_locale_string (obj_p);
    }

    ecma_deref_object (obj_p);

    return ret_value;
  }

  JERRY_ASSERT (builtin_routine_id >= ECMA_OBJECT_PROTOTYPE_HAS_OWN_PROPERTY);

  ecma_string_t *prop_name_p = ecma_op_to_prop_name (arguments_list_p[0]);

  if (prop_name_p == NULL)
  {
    return ECMA_VALUE_ERROR;
  }

  ecma_value_t to_object = ecma_op_to_object (this_arg);

  if (ECMA_IS_VALUE_ERROR (to_object))
  {
    ecma_deref_ecma_string (prop_name_p);
    return to_object;
  }

  ecma_object_t *obj_p = ecma_get_object_from_value (to_object);

  ecma_value_t ret_value;

  if (builtin_routine_id == ECMA_OBJECT_PROTOTYPE_HAS_OWN_PROPERTY)
  {
    ret_value = ecma_builtin_object_prototype_object_has_own_property (obj_p, prop_name_p);
  }
  else
  {
    ret_value = ecma_builtin_object_prototype_object_property_is_enumerable (obj_p, prop_name_p);
  }

  ecma_deref_ecma_string (prop_name_p);
  ecma_deref_object (obj_p);

  return ret_value;
}