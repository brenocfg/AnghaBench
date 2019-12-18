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
typedef  int /*<<< orphan*/  jerryx_arg_t ;
struct TYPE_3__ {int c_arg_cnt; int /*<<< orphan*/ * c_arg_p; } ;
typedef  TYPE_1__ jerryx_arg_array_items_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_length_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JERRYX_ARG_COERCE ; 
 int /*<<< orphan*/  JERRYX_ARG_OPTIONAL ; 
 int /*<<< orphan*/  JERRYX_ARG_REQUIRED ; 
 int /*<<< orphan*/  JERRY_UNUSED (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_array (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_number (double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_transform_args (int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ validator_array_count ; 

__attribute__((used)) static jerry_value_t
test_validator_array1_handler (const jerry_value_t func_obj_val, /**< function object */
                               const jerry_value_t this_val, /**< this value */
                               const jerry_value_t args_p[], /**< arguments list */
                               const jerry_length_t args_cnt) /**< arguments length */
{
  JERRY_UNUSED (func_obj_val);
  JERRY_UNUSED (this_val);

  double native1 = 0;
  double native2 = 0;
  double native3 = 0;

  jerryx_arg_array_items_t arr_info;

  jerryx_arg_t item_mapping[] =
  {
    jerryx_arg_number (&native1, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    jerryx_arg_number (&native2, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    jerryx_arg_number (&native3, JERRYX_ARG_COERCE, JERRYX_ARG_OPTIONAL)
  };

  arr_info.c_arg_p = item_mapping;
  arr_info.c_arg_cnt = 3;

  jerryx_arg_t mapping[] =
  {
    jerryx_arg_array (&arr_info, JERRYX_ARG_OPTIONAL),
  };

  jerry_value_t is_ok = jerryx_arg_transform_args (args_p, args_cnt, mapping, ARRAY_SIZE (mapping));


  TEST_ASSERT (!jerry_value_is_error (is_ok));

  if (validator_array_count == 0)
  {
    TEST_ASSERT (native1 == 1);
    TEST_ASSERT (native2 == 2);
    TEST_ASSERT (native3 == 0);
  }

  validator_array_count++;

  return jerry_create_undefined ();
}