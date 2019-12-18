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
typedef  char const* jerryx_arg_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_length_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  JERRYX_ARG_COERCE ; 
 int /*<<< orphan*/  JERRYX_ARG_REQUIRED ; 
 int /*<<< orphan*/  JERRY_UNUSED (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_value_is_error (int /*<<< orphan*/ ) ; 
 char const* jerryx_arg_boolean (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_transform_object_properties (int /*<<< orphan*/  const,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validator_prop_count ; 

__attribute__((used)) static jerry_value_t
test_validator_prop3_handler (const jerry_value_t func_obj_val, /**< function object */
                              const jerry_value_t this_val, /**< this value */
                              const jerry_value_t args_p[], /**< arguments list */
                              const jerry_length_t args_cnt) /**< arguments length */
{
  JERRY_UNUSED (func_obj_val);
  JERRY_UNUSED (this_val);
  JERRY_UNUSED (args_cnt);

  bool native1 = false;
  bool native2 = true;

  const char *name_p[] = { "prop1", "prop2" };

  jerryx_arg_t mapping[] =
  {
    jerryx_arg_boolean (&native1, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
    jerryx_arg_boolean (&native2, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
  };

  jerry_value_t is_ok = jerryx_arg_transform_object_properties (args_p[0],
                                                                (const jerry_char_t **) name_p,
                                                                ARRAY_SIZE (name_p),
                                                                mapping,
                                                                ARRAY_SIZE (mapping));

  TEST_ASSERT (jerry_value_is_error (is_ok));
  TEST_ASSERT (!native1);
  TEST_ASSERT (native2);

  validator_prop_count++;
  jerry_release_value (is_ok);

  return jerry_create_undefined ();
}