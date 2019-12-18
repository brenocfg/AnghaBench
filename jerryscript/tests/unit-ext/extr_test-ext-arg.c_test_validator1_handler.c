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
 int /*<<< orphan*/  JERRYX_ARG_OPTIONAL ; 
 int /*<<< orphan*/  JERRYX_ARG_REQUIRED ; 
 int /*<<< orphan*/  JERRY_UNUSED (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int jerry_value_is_function (int /*<<< orphan*/ ) ; 
 int jerry_value_is_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_boolean (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_ignore () ; 
 int /*<<< orphan*/  jerryx_arg_number (double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_string (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_transform_this_and_args (int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int validator1_count ; 

__attribute__((used)) static jerry_value_t
test_validator1_handler (const jerry_value_t func_obj_val, /**< function object */
                         const jerry_value_t this_val, /**< this value */
                         const jerry_value_t args_p[], /**< arguments list */
                         const jerry_length_t args_cnt) /**< arguments length */
{
  JERRY_UNUSED (func_obj_val);

  bool arg1;
  double arg2 = 0.0;
  char arg3[5] = "1234";
  jerry_value_t arg4 = jerry_create_undefined ();

  jerryx_arg_t mapping[] =
  {
    /* ignore this */
    jerryx_arg_ignore (),
    /* 1st argument should be boolean */
    jerryx_arg_boolean (&arg1, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    /* 2nd argument should be strict number */
    jerryx_arg_number (&arg2, JERRYX_ARG_NO_COERCE, JERRYX_ARG_REQUIRED),
    /* 3th argument should be string */
    jerryx_arg_string (arg3, 5, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    /* 4th argument should be function, and it is optional */
    jerryx_arg_function (&arg4, JERRYX_ARG_OPTIONAL)
  };

  jerry_value_t is_ok = jerryx_arg_transform_this_and_args (this_val,
                                                            args_p,
                                                            args_cnt,
                                                            mapping,
                                                            ARRAY_SIZE (mapping));

  if (validator1_count == 0)
  {
    TEST_ASSERT (!jerry_value_is_error (is_ok));
    TEST_ASSERT (arg1);
    TEST_ASSERT (arg2 == 10.5);
    TEST_ASSERT (strcmp (arg3, "abc") == 0);
    TEST_ASSERT (jerry_value_is_function (arg4));
  }
  else if (validator1_count == 1)
  {
    TEST_ASSERT (!jerry_value_is_error (is_ok));
    TEST_ASSERT (arg1);
    TEST_ASSERT (arg2 == 10.5);
    TEST_ASSERT (strcmp (arg3, "abc") == 0);
    TEST_ASSERT (jerry_value_is_undefined (arg4));
  }
  else if (validator1_count == 2)
  {
    TEST_ASSERT (!jerry_value_is_error (is_ok));
    TEST_ASSERT (arg1);
    TEST_ASSERT (arg2 == 10.5);
    TEST_ASSERT (strcmp (arg3, "") == 0);
    TEST_ASSERT (jerry_value_is_undefined (arg4));
  }
  else
  {
    TEST_ASSERT (jerry_value_is_error (is_ok));
  }

  jerry_release_value (is_ok);
  jerry_release_value (arg4);
  validator1_count++;

  return jerry_create_undefined ();
}