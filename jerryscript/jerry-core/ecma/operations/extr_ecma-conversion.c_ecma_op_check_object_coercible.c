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

/* Variables and functions */
 int /*<<< orphan*/  ECMA_ERR_MSG (char*) ; 
 int /*<<< orphan*/  ECMA_VALUE_EMPTY ; 
 int /*<<< orphan*/  ecma_check_value_type_is_spec_defined (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_null (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_raise_type_error (int /*<<< orphan*/ ) ; 

ecma_value_t
ecma_op_check_object_coercible (ecma_value_t value) /**< ecma value */
{
  ecma_check_value_type_is_spec_defined (value);

  if (ecma_is_value_undefined (value)
      || ecma_is_value_null (value))
  {
    return ecma_raise_type_error (ECMA_ERR_MSG ("Argument cannot be converted to an object."));
  }
  else
  {
    return ECMA_VALUE_EMPTY;
  }
}