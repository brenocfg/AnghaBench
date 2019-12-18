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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JERRYX_ARG_COERCE ; 
 int /*<<< orphan*/  JERRYX_ARG_NO_COERCE ; 
 int /*<<< orphan*/  JERRYX_ARG_REQUIRED ; 
 int /*<<< orphan*/  JERRY_UNUSED (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_boolean (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_number (double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_transform_array (int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validator_array_count ; 

__attribute__((used)) static jerry_value_t
test_validator_array2_handler (const jerry_value_t func_obj_val, /**< function object */
                               const jerry_value_t this_val, /**< this value */
                               const jerry_value_t args_p[], /**< arguments list */
                               const jerry_length_t args_cnt) /**< arguments length */
{
  JERRY_UNUSED (func_obj_val);
  JERRY_UNUSED (this_val);
  JERRY_UNUSED (args_cnt);

  double native1 = 0;
  bool native2 = false;

  jerryx_arg_t item_mapping[] =
  {
    jerryx_arg_number (&native1, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    jerryx_arg_boolean (&native2, JERRYX_ARG_NO_COERCE, JERRYX_ARG_REQUIRED)
  };

  jerry_value_t is_ok = jerryx_arg_transform_array (args_p[0], item_mapping, ARRAY_SIZE (item_mapping));

  TEST_ASSERT (jerry_value_is_error (is_ok));
  TEST_ASSERT (native1 == 1);
  TEST_ASSERT (!native2);

  validator_array_count++;
  jerry_release_value (is_ok);

  return jerry_create_undefined ();
}