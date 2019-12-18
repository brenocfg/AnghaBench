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
typedef  int number_arithmetic_op ;
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int ecma_number_t ;

/* Variables and functions */
 int ECMA_NUMBER_ZERO ; 
 int /*<<< orphan*/  ECMA_OP_TO_NUMBER_FINALIZE (int) ; 
 int /*<<< orphan*/  ECMA_OP_TO_NUMBER_TRY_CATCH (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_VALUE_EMPTY ; 
#define  NUMBER_ARITHMETIC_DIVISION 131 
#define  NUMBER_ARITHMETIC_MULTIPLICATION 130 
#define  NUMBER_ARITHMETIC_REMAINDER 129 
#define  NUMBER_ARITHMETIC_SUBTRACTION 128 
 int /*<<< orphan*/  ecma_make_number_value (int) ; 
 int ecma_op_number_remainder (int,int) ; 
 int num_left ; 
 int num_right ; 

ecma_value_t
do_number_arithmetic (number_arithmetic_op op, /**< number arithmetic operation */
                      ecma_value_t left_value, /**< left value */
                      ecma_value_t right_value) /**< right value */
{
  ecma_value_t ret_value = ECMA_VALUE_EMPTY;

  ECMA_OP_TO_NUMBER_TRY_CATCH (num_left, left_value, ret_value);
  ECMA_OP_TO_NUMBER_TRY_CATCH (num_right, right_value, ret_value);

  ecma_number_t result = ECMA_NUMBER_ZERO;

  switch (op)
  {
    case NUMBER_ARITHMETIC_SUBTRACTION:
    {
      result = num_left - num_right;
      break;
    }
    case NUMBER_ARITHMETIC_MULTIPLICATION:
    {
      result = num_left * num_right;
      break;
    }
    case NUMBER_ARITHMETIC_DIVISION:
    {
      result = num_left / num_right;
      break;
    }
    case NUMBER_ARITHMETIC_REMAINDER:
    {
      result = ecma_op_number_remainder (num_left, num_right);
      break;
    }
  }

  ret_value = ecma_make_number_value (result);

  ECMA_OP_TO_NUMBER_FINALIZE (num_right);
  ECMA_OP_TO_NUMBER_FINALIZE (num_left);

  return ret_value;
}