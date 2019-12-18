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
typedef  int /*<<< orphan*/  ecma_property_descriptor_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_VALUE_UNDEFINED ; 
 int /*<<< orphan*/  ecma_free_property_descriptor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_make_object_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_op_from_property_descriptor (int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_op_object_get_own_property_descriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ecma_value_t
ecma_builtin_object_object_get_own_property_descriptor (ecma_object_t *obj_p, /**< routine's first argument */
                                                        ecma_string_t *name_str_p) /**< routine's second argument */
{
  /* 3. */
  ecma_property_descriptor_t prop_desc;

  if (ecma_op_object_get_own_property_descriptor (obj_p, name_str_p, &prop_desc))
  {
    /* 4. */
    ecma_object_t *desc_obj_p = ecma_op_from_property_descriptor (&prop_desc);

    ecma_free_property_descriptor (&prop_desc);

    return ecma_make_object_value (desc_obj_p);
  }

  return ECMA_VALUE_UNDEFINED;
}