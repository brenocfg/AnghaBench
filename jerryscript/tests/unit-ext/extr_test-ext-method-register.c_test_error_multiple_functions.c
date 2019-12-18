#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_4__ {int registered; int result; } ;
typedef  TYPE_1__ jerryx_register_result ;
typedef  int /*<<< orphan*/  jerryx_property_entry ;
typedef  int jerry_value_t ;
typedef  size_t jerry_size_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  JERRYX_PROPERTY_FUNCTION (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JERRYX_PROPERTY_LIST_END () ; 
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  freeze_property (int,char const*) ; 
 int jerry_call_function (int,int /*<<< orphan*/ ,int*,size_t) ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int jerry_create_number (int) ; 
 int jerry_create_object () ; 
 int jerry_create_string (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int jerry_get_boolean_value (int) ; 
 scalar_t__ jerry_get_number_value (int) ; 
 int jerry_get_property (int,int) ; 
 int jerry_has_own_property (int,int) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int) ; 
 int jerry_value_is_error (int) ; 
 int jerry_value_is_function (int) ; 
 int jerry_value_is_number (int) ; 
 int /*<<< orphan*/  jerryx_release_property_entry (int /*<<< orphan*/ *,TYPE_1__) ; 
 TYPE_1__ jerryx_set_properties (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  method_hello ; 

__attribute__((used)) static void
test_error_multiple_functions (void)
{
  jerry_init (JERRY_INIT_EMPTY);

  const char *prop_ok = "prop_ok";
  const char *prop_err = "prop_err";
  const char *prop_not = "prop_not";
  jerry_value_t target_object = jerry_create_object ();
  freeze_property (target_object, prop_err);

  jerryx_property_entry methods[] =
  {
    JERRYX_PROPERTY_FUNCTION (prop_ok, method_hello), // This registration is ok
    JERRYX_PROPERTY_FUNCTION (prop_err, method_hello), // This registration should fail
    JERRYX_PROPERTY_FUNCTION (prop_not, method_hello), // This registration is not done
    JERRYX_PROPERTY_LIST_END (),
  };

  jerryx_register_result register_result = jerryx_set_properties (target_object, methods);

  TEST_ASSERT (register_result.registered == 1);
  TEST_ASSERT (jerry_value_is_error (register_result.result));

  jerryx_release_property_entry (methods, register_result);
  jerry_release_value (register_result.result);

  {
    // Test if property "prop_ok" is correctly registered.
    jerry_value_t prop_ok_val = jerry_create_string ((const jerry_char_t *) prop_ok);
    jerry_value_t prop_ok_exists = jerry_has_own_property (target_object, prop_ok_val);
    TEST_ASSERT (jerry_get_boolean_value (prop_ok_exists) == true);
    jerry_release_value (prop_ok_exists);

    // Try calling the method
    jerry_value_t prop_ok_func = jerry_get_property (target_object, prop_ok_val);
    TEST_ASSERT (jerry_value_is_function (prop_ok_func) == true);
    jerry_value_t args[2] =
    {
      jerry_create_number (22),
      jerry_create_number (-3),
    };
    jerry_size_t args_cnt = sizeof (args) / sizeof (jerry_value_t);
    jerry_value_t func_result = jerry_call_function (prop_ok_func,
                                                     jerry_create_undefined (),
                                                     args,
                                                     args_cnt);
    TEST_ASSERT (jerry_value_is_number (func_result) == true);
    TEST_ASSERT ((uint32_t) jerry_get_number_value (func_result) == 2u);
    jerry_release_value (func_result);
    for (jerry_size_t idx = 0; idx < args_cnt; idx++)
    {
      jerry_release_value (args[idx]);
    }
    jerry_release_value (prop_ok_func);
    jerry_release_value (prop_ok_val);
  }

  {
    // The "prop_err" should exist - as it was "freezed" - but it should not be a function
    jerry_value_t prop_err_val = jerry_create_string ((const jerry_char_t *) prop_err);
    jerry_value_t prop_err_exists = jerry_has_own_property (target_object, prop_err_val);
    TEST_ASSERT (jerry_get_boolean_value (prop_err_exists) == true);
    jerry_release_value (prop_err_exists);

    jerry_value_t prop_err_func = jerry_value_is_function (prop_err_val);
    TEST_ASSERT (jerry_value_is_function (prop_err_func) == false);
    jerry_release_value (prop_err_val);
  }

  { // The "prop_not" is not available on the target object
    jerry_value_t prop_not_val = jerry_create_string ((const jerry_char_t *) prop_not);
    jerry_value_t prop_not_exists = jerry_has_own_property (target_object, prop_not_val);
    TEST_ASSERT (jerry_get_boolean_value (prop_not_exists) == false);
    jerry_release_value (prop_not_exists);
    jerry_release_value (prop_not_val);
  }

  jerry_release_value (target_object);

  jerry_cleanup ();
}