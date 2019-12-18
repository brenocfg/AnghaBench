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
typedef  int uint32_t ;
typedef  int number_bitwise_logic_op ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_IS_VALUE_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_NUMBER_ZERO ; 
 int /*<<< orphan*/  ECMA_OP_TO_NUMBER_FINALIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_OP_TO_NUMBER_TRY_CATCH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_VALUE_EMPTY ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
#define  NUMBER_BITWISE_LOGIC_AND 134 
#define  NUMBER_BITWISE_LOGIC_OR 133 
#define  NUMBER_BITWISE_LOGIC_XOR 132 
#define  NUMBER_BITWISE_NOT 131 
#define  NUMBER_BITWISE_SHIFT_LEFT 130 
#define  NUMBER_BITWISE_SHIFT_RIGHT 129 
#define  NUMBER_BITWISE_SHIFT_URIGHT 128 
 int /*<<< orphan*/  ecma_make_number_value (int /*<<< orphan*/ ) ; 
 int ecma_number_to_int32 (int /*<<< orphan*/ ) ; 
 int ecma_number_to_uint32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_left ; 
 int /*<<< orphan*/  num_right ; 

ecma_value_t
do_number_bitwise_logic (number_bitwise_logic_op op, /**< number bitwise logic operation */
                         ecma_value_t left_value, /**< left value */
                         ecma_value_t right_value) /**< right value */
{
  JERRY_ASSERT (!ECMA_IS_VALUE_ERROR (left_value)
                && !ECMA_IS_VALUE_ERROR (right_value));

  ecma_value_t ret_value = ECMA_VALUE_EMPTY;

  ECMA_OP_TO_NUMBER_TRY_CATCH (num_left, left_value, ret_value);
  ECMA_OP_TO_NUMBER_TRY_CATCH (num_right, right_value, ret_value);

  ecma_number_t result = ECMA_NUMBER_ZERO;
  uint32_t right_uint32 = ecma_number_to_uint32 (num_right);

  switch (op)
  {
    case NUMBER_BITWISE_LOGIC_AND:
    {
      uint32_t left_uint32 = ecma_number_to_uint32 (num_left);
      result = (ecma_number_t) ((int32_t) (left_uint32 & right_uint32));
      break;
    }
    case NUMBER_BITWISE_LOGIC_OR:
    {
      uint32_t left_uint32 = ecma_number_to_uint32 (num_left);
      result = (ecma_number_t) ((int32_t) (left_uint32 | right_uint32));
      break;
    }
    case NUMBER_BITWISE_LOGIC_XOR:
    {
      uint32_t left_uint32 = ecma_number_to_uint32 (num_left);
      result = (ecma_number_t) ((int32_t) (left_uint32 ^ right_uint32));
      break;
    }
    case NUMBER_BITWISE_SHIFT_LEFT:
    {
      result = (ecma_number_t) (ecma_number_to_int32 (num_left) << (right_uint32 & 0x1F));
      break;
    }
    case NUMBER_BITWISE_SHIFT_RIGHT:
    {
      result = (ecma_number_t) (ecma_number_to_int32 (num_left) >> (right_uint32 & 0x1F));
      break;
    }
    case NUMBER_BITWISE_SHIFT_URIGHT:
    {
      uint32_t left_uint32 = ecma_number_to_uint32 (num_left);
      result = (ecma_number_t) (left_uint32 >> (right_uint32 & 0x1F));
      break;
    }
    case NUMBER_BITWISE_NOT:
    {
      result = (ecma_number_t) ((int32_t) ~right_uint32);
      break;
    }
  }

  ret_value = ecma_make_number_value (result);

  ECMA_OP_TO_NUMBER_FINALIZE (num_right);
  ECMA_OP_TO_NUMBER_FINALIZE (num_left);

  return ret_value;
}