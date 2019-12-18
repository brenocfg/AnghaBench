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
typedef  int /*<<< orphan*/  ecma_preferred_type_hint_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ecma_check_value_type_is_spec_defined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_copy_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_get_object_from_value (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_op_object_default_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ecma_value_t
ecma_op_to_primitive (ecma_value_t value, /**< ecma value */
                      ecma_preferred_type_hint_t preferred_type) /**< preferred type hint */
{
  ecma_check_value_type_is_spec_defined (value);

  if (ecma_is_value_object (value))
  {
    ecma_object_t *obj_p = ecma_get_object_from_value (value);

    return ecma_op_object_default_value (obj_p, preferred_type);
  }
  else
  {
    return ecma_copy_value (value);
  }
}