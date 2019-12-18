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
typedef  int /*<<< orphan*/  jerryx_arg_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_length_t ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JERRYX_ARG_CEIL ; 
 int /*<<< orphan*/  JERRYX_ARG_CLAMP ; 
 int /*<<< orphan*/  JERRYX_ARG_COERCE ; 
 int /*<<< orphan*/  JERRYX_ARG_FLOOR ; 
 int /*<<< orphan*/  JERRYX_ARG_NO_CLAMP ; 
 int /*<<< orphan*/  JERRYX_ARG_REQUIRED ; 
 int /*<<< orphan*/  JERRYX_ARG_ROUND ; 
 int /*<<< orphan*/  JERRY_UNUSED (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_int8 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_transform_args (int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validator_int_count ; 

__attribute__((used)) static jerry_value_t
test_validator_int2_handler (const jerry_value_t func_obj_val, /**< function object */
                             const jerry_value_t this_val, /**< this value */
                             const jerry_value_t args_p[], /**< arguments list */
                             const jerry_length_t args_cnt) /**< arguments length */
{
  JERRY_UNUSED (func_obj_val);
  JERRY_UNUSED (this_val);

  int8_t num0, num1, num2, num3, num4, num5, num6, num7, num8, num9;
  num8 = 123;
  num9 = 123;

  jerryx_arg_t mapping[] =
  {
    jerryx_arg_int8 (&num0, JERRYX_ARG_ROUND, JERRYX_ARG_CLAMP, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    jerryx_arg_int8 (&num1, JERRYX_ARG_FLOOR, JERRYX_ARG_CLAMP, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    jerryx_arg_int8 (&num2, JERRYX_ARG_CEIL, JERRYX_ARG_CLAMP, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    jerryx_arg_int8 (&num3, JERRYX_ARG_ROUND, JERRYX_ARG_CLAMP, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    jerryx_arg_int8 (&num4, JERRYX_ARG_FLOOR, JERRYX_ARG_CLAMP, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    jerryx_arg_int8 (&num5, JERRYX_ARG_CEIL, JERRYX_ARG_CLAMP, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    jerryx_arg_int8 (&num6, JERRYX_ARG_ROUND, JERRYX_ARG_CLAMP, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    jerryx_arg_int8 (&num7, JERRYX_ARG_ROUND, JERRYX_ARG_CLAMP, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    jerryx_arg_int8 (&num8, JERRYX_ARG_ROUND, JERRYX_ARG_CLAMP, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    jerryx_arg_int8 (&num9, JERRYX_ARG_ROUND, JERRYX_ARG_NO_CLAMP, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
  };

  jerry_value_t is_ok = jerryx_arg_transform_args (args_p,
                                                   args_cnt,
                                                   mapping,
                                                   ARRAY_SIZE (mapping));

  TEST_ASSERT (jerry_value_is_error (is_ok));
  TEST_ASSERT (num0 == -2);
  TEST_ASSERT (num1 == -2);
  TEST_ASSERT (num2 == -1);
  TEST_ASSERT (num3 == 2);
  TEST_ASSERT (num4 == 1);
  TEST_ASSERT (num5 == 2);
  TEST_ASSERT (num6 == 127);
  TEST_ASSERT (num7 == -128);
  TEST_ASSERT (num8 == 127);
  TEST_ASSERT (num9 == 123);

  jerry_release_value (is_ok);
  validator_int_count++;

  return jerry_create_undefined ();
}