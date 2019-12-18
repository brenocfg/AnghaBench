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
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ expected; int /*<<< orphan*/  rhs; int /*<<< orphan*/  lhs; } ;
typedef  TYPE_1__ test_entry_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;
typedef  int /*<<< orphan*/  error_tests ;
typedef  int /*<<< orphan*/  bool_tests ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_BIN_OP_INSTANCEOF ; 
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 TYPE_1__ T (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_INIT () ; 
 int /*<<< orphan*/  jerry_acquire_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_binary_operation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_construct_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_create_array (int) ; 
 int /*<<< orphan*/  jerry_create_error_from_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jerry_create_external_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_create_null () ; 
 int /*<<< orphan*/  jerry_create_number (double) ; 
 int /*<<< orphan*/  jerry_create_object () ; 
 int /*<<< orphan*/  jerry_create_string (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 scalar_t__ jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_constructor ; 

int
main (void)
{
  TEST_INIT ();

  jerry_init (JERRY_INIT_EMPTY);

  jerry_value_t base_obj = jerry_create_object ();
  jerry_value_t constructor = jerry_create_external_function (my_constructor);

  jerry_value_t no_proto_instance_val = jerry_construct_object (constructor, NULL, 0);

  jerry_value_t prototype_str = jerry_create_string ((const jerry_char_t *) "prototype");
  jerry_value_t res = jerry_set_property (constructor, prototype_str, base_obj);
  jerry_release_value (prototype_str);
  TEST_ASSERT (!jerry_value_is_error (res));
  jerry_release_value (res);

  jerry_value_t instance_val = jerry_construct_object (constructor, NULL, 0);

  jerry_value_t error = jerry_create_error_from_value (base_obj, false);

  test_entry_t bool_tests[] =
  {
    T (jerry_acquire_value (instance_val), jerry_acquire_value (constructor), true),
    T (jerry_acquire_value (no_proto_instance_val), jerry_acquire_value (constructor), false),
    T (jerry_acquire_value (base_obj), jerry_acquire_value (constructor), false)
  };

  for (uint32_t idx = 0; idx < sizeof (bool_tests) / sizeof (test_entry_t); idx++)
  {
    jerry_value_t result = jerry_binary_operation (JERRY_BIN_OP_INSTANCEOF,
                                                   bool_tests[idx].lhs,
                                                   bool_tests[idx].rhs);
    TEST_ASSERT (!jerry_value_is_error (result));
    TEST_ASSERT (jerry_get_boolean_value (result) == bool_tests[idx].expected);
    jerry_release_value (bool_tests[idx].lhs);
    jerry_release_value (bool_tests[idx].rhs);
    jerry_release_value (result);
  }

  test_entry_t error_tests[] =
  {
    T (jerry_acquire_value (constructor), jerry_acquire_value (instance_val), true),
    T (jerry_create_undefined (), jerry_acquire_value (constructor), true),
    T (jerry_acquire_value (instance_val), jerry_create_undefined (), true),
    T (jerry_acquire_value (instance_val), jerry_acquire_value (base_obj), true),
    T (jerry_acquire_value (error), jerry_acquire_value (constructor), true),
    T (jerry_acquire_value (instance_val), jerry_acquire_value (error), true),
    T (jerry_create_string ((const jerry_char_t *) ""), jerry_create_string ((const jerry_char_t *) ""), true),
    T (jerry_create_string ((const jerry_char_t *) ""), jerry_create_number (5.0), true),
    T (jerry_create_number (5.0), jerry_create_string ((const jerry_char_t *) ""), true),
    T (jerry_create_array (1), jerry_create_array (1), true),
    T (jerry_create_array (1), jerry_create_object (), true),
    T (jerry_create_object (), jerry_create_array (1), true),
    T (jerry_create_null (), jerry_create_object (), true),
    T (jerry_create_object (), jerry_create_string ((const jerry_char_t *) ""), true)
  };

  for (uint32_t idx = 0; idx < sizeof (error_tests) / sizeof (test_entry_t); idx++)
  {
    jerry_value_t result = jerry_binary_operation (JERRY_BIN_OP_INSTANCEOF,
                                                   error_tests[idx].lhs,
                                                   error_tests[idx].rhs);
    TEST_ASSERT (jerry_value_is_error (result) == error_tests[idx].expected);
    jerry_release_value (error_tests[idx].lhs);
    jerry_release_value (error_tests[idx].rhs);
    jerry_release_value (result);
  }

  jerry_release_value (base_obj);
  jerry_release_value (constructor);
  jerry_release_value (error);
  jerry_release_value (instance_val);
  jerry_release_value (no_proto_instance_val);

  jerry_cleanup ();

  return 0;
}