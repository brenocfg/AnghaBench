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
 int /*<<< orphan*/  ECMA_OP_TO_NUMBER_FINALIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_OP_TO_NUMBER_TRY_CATCH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_VALUE_EMPTY ; 
 int /*<<< orphan*/  ecma_make_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_var_value ; 

ecma_value_t
opfunc_unary_operation (ecma_value_t left_value, /**< left value */
                        bool is_plus) /**< unary plus flag */
{
  ecma_value_t ret_value = ECMA_VALUE_EMPTY;

  ECMA_OP_TO_NUMBER_TRY_CATCH (num_var_value,
                               left_value,
                               ret_value);

  ret_value = ecma_make_number_value (is_plus ? num_var_value : -num_var_value);

  ECMA_OP_TO_NUMBER_FINALIZE (num_var_value);

  return ret_value;
}