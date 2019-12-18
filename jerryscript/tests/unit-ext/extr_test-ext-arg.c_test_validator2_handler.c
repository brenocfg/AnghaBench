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
struct TYPE_3__ {int x; } ;
typedef  TYPE_1__ my_type_a_t ;
typedef  int /*<<< orphan*/  jerryx_arg_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_length_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JERRYX_ARG_REQUIRED ; 
 int /*<<< orphan*/  JERRY_UNUSED (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_custom (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_native_pointer (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_transform_this_and_args (int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_custom_transform ; 
 TYPE_1__ my_thing_a ; 
 int /*<<< orphan*/  thing_a_info ; 
 scalar_t__ validator2_count ; 

__attribute__((used)) static jerry_value_t
test_validator2_handler (const jerry_value_t func_obj_val, /**< function object */
                         const jerry_value_t this_val, /**< this value */
                         const jerry_value_t args_p[], /**< arguments list */
                         const jerry_length_t args_cnt) /**< arguments length */
{
  JERRY_UNUSED (func_obj_val);

  my_type_a_t *thing_p;

  jerryx_arg_t mapping[] =
  {
    /* this should has native pointer, whose type is thing_a_info */
    jerryx_arg_native_pointer ((void **) &thing_p, &thing_a_info, JERRYX_ARG_REQUIRED),
    /* custom tranform function */
    jerryx_arg_custom (NULL, 5, my_custom_transform)
  };

  jerry_value_t is_ok = jerryx_arg_transform_this_and_args (this_val,
                                                            args_p,
                                                            args_cnt,
                                                            mapping,
                                                            ARRAY_SIZE (mapping));

  if (validator2_count == 0)
  {
    TEST_ASSERT (!jerry_value_is_error (is_ok));
    TEST_ASSERT (thing_p == &my_thing_a);
    TEST_ASSERT (thing_p->x == 1);
  }
  else
  {
    TEST_ASSERT (jerry_value_is_error (is_ok));
  }

  jerry_release_value (is_ok);
  validator2_count++;

  return jerry_create_undefined ();
}