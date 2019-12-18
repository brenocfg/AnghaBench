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
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int /*<<< orphan*/  ecma_check_value_type_is_spec_defined (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_boolean (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_null (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_number (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_object (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_prop_name (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_make_object_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_op_create_object_object_noarg () ; 
 int /*<<< orphan*/  ecma_op_to_object (int /*<<< orphan*/ ) ; 

ecma_value_t
ecma_op_create_object_object_arg (ecma_value_t value) /**< argument of constructor */
{
  ecma_check_value_type_is_spec_defined (value);

  if (ecma_is_value_object (value)
      || ecma_is_value_number (value)
      || ecma_is_value_prop_name (value)
      || ecma_is_value_boolean (value))
  {
    /* 1.b, 1.c, 1.d */
    return ecma_op_to_object (value);
  }
  else
  {
    /* 2. */
    JERRY_ASSERT (ecma_is_value_undefined (value)
                  || ecma_is_value_null (value));

    ecma_object_t *obj_p = ecma_op_create_object_object_noarg ();

    return ecma_make_object_value (obj_p);
  }
}