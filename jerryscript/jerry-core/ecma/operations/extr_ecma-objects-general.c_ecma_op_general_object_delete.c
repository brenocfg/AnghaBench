#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_string_t ;
typedef  scalar_t__ ecma_property_t ;
struct TYPE_3__ {int /*<<< orphan*/  value_p; } ;
typedef  TYPE_1__ ecma_property_ref_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_ERR_MSG (char*) ; 
 scalar_t__ ECMA_OBJECT_TYPE_ARRAY ; 
 int /*<<< orphan*/  ECMA_PROPERTY_GET_NO_OPTIONS ; 
 scalar_t__ ECMA_PROPERTY_TYPE_NOT_FOUND ; 
 scalar_t__ ECMA_PROPERTY_TYPE_NOT_FOUND_AND_STOP ; 
 int /*<<< orphan*/  ECMA_VALUE_FALSE ; 
 int /*<<< orphan*/  ECMA_VALUE_TRUE ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int /*<<< orphan*/  ecma_array_object_delete_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_delete_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_get_object_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_is_lexical_environment (int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_is_property_configurable (scalar_t__) ; 
 scalar_t__ ecma_op_object_get_own_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_raise_type_error (int /*<<< orphan*/ ) ; 

ecma_value_t
ecma_op_general_object_delete (ecma_object_t *obj_p, /**< the object */
                               ecma_string_t *property_name_p, /**< property name */
                               bool is_throw) /**< flag that controls failure handling */
{
  JERRY_ASSERT (obj_p != NULL
                && !ecma_is_lexical_environment (obj_p));
  JERRY_ASSERT (property_name_p != NULL);

  /* 1. */
  ecma_property_ref_t property_ref;

  ecma_property_t property = ecma_op_object_get_own_property (obj_p,
                                                              property_name_p,
                                                              &property_ref,
                                                              ECMA_PROPERTY_GET_NO_OPTIONS);

  /* 2. */
  if (property == ECMA_PROPERTY_TYPE_NOT_FOUND || property == ECMA_PROPERTY_TYPE_NOT_FOUND_AND_STOP)
  {
    return ECMA_VALUE_TRUE;
  }

  /* 3. */
  if (ecma_is_property_configurable (property))
  {
    if (ecma_get_object_type (obj_p) == ECMA_OBJECT_TYPE_ARRAY)
    {
      ecma_array_object_delete_property (obj_p, property_name_p, property_ref.value_p);
    }
    else
    {
      /* a. */
      ecma_delete_property (obj_p, property_ref.value_p);
    }

    /* b. */
    return ECMA_VALUE_TRUE;
  }

  /* 4. */
  if (is_throw)
  {
    return ecma_raise_type_error (ECMA_ERR_MSG ("Expected a configurable property."));
  }

  /* 5. */
  return ECMA_VALUE_FALSE;
}