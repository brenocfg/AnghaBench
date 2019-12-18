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
struct TYPE_4__ {int registered; int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ jerryx_register_result ;
typedef  int /*<<< orphan*/  jerryx_property_entry ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRYX_PROPERTY_BOOLEAN (char*,int) ; 
 int /*<<< orphan*/  JERRYX_PROPERTY_FUNCTION (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JERRYX_PROPERTY_LIST_END () ; 
 int /*<<< orphan*/  JERRYX_PROPERTY_NUMBER (char*,double) ; 
 int /*<<< orphan*/  JERRYX_PROPERTY_STRING (char*,char*) ; 
 int /*<<< orphan*/  JERRYX_PROPERTY_STRING_SZ (char*,char*,int) ; 
 int /*<<< orphan*/  JERRYX_PROPERTY_UNDEFINED (char*) ; 
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_create_object () ; 
 int /*<<< orphan*/  jerry_eval (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_global_object () ; 
 double jerry_get_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_value_is_boolean (int /*<<< orphan*/ ) ; 
 int jerry_value_is_number (int /*<<< orphan*/ ) ; 
 int jerry_value_is_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_release_property_entry (int /*<<< orphan*/ *,TYPE_1__) ; 
 TYPE_1__ jerryx_set_properties (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerryx_set_property_str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  method_hello ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
test_simple_registration (void)
{
  jerry_init (JERRY_INIT_EMPTY);

  jerry_value_t target_object = jerry_create_object ();

  // Test simple registration
  jerryx_property_entry methods[] =
  {
    JERRYX_PROPERTY_FUNCTION ("hello", method_hello),
    JERRYX_PROPERTY_NUMBER ("my_number", 42.5),
    JERRYX_PROPERTY_STRING ("my_str", "super_str"),
    JERRYX_PROPERTY_STRING_SZ ("my_str_sz", "super_str", 6),
    JERRYX_PROPERTY_BOOLEAN ("my_bool", true),
    JERRYX_PROPERTY_BOOLEAN ("my_bool_false", false),
    JERRYX_PROPERTY_UNDEFINED ("my_non_value"),
    JERRYX_PROPERTY_LIST_END (),
  };

  jerryx_register_result register_result = jerryx_set_properties (target_object, methods);

  TEST_ASSERT (register_result.registered == 7);
  TEST_ASSERT (jerry_value_is_undefined (register_result.result));

  jerryx_release_property_entry (methods, register_result);
  jerry_release_value (register_result.result);

  jerry_value_t global_obj = jerry_get_global_object ();
  jerryx_set_property_str (global_obj, "test", target_object);
  jerry_release_value (target_object);
  jerry_release_value (global_obj);

  {
    const char *test_A = "test.my_number";
    jerry_value_t result = jerry_eval ((const jerry_char_t *) test_A, strlen (test_A), 0);
    TEST_ASSERT (jerry_value_is_number (result));
    TEST_ASSERT (jerry_get_number_value (result) == 42.5);
    jerry_release_value (result);
  }

  {
    const char *test_A = "test.my_str_sz === 'super_'";
    jerry_value_t result = jerry_eval ((const jerry_char_t *) test_A, strlen (test_A), 0);
    TEST_ASSERT (jerry_value_is_boolean (result));
    TEST_ASSERT (jerry_get_boolean_value (result) == true);
    jerry_release_value (result);
  }

  {
    const char *test_A = "test.my_str === 'super_str'";
    jerry_value_t result = jerry_eval ((const jerry_char_t *) test_A, strlen (test_A), 0);
    TEST_ASSERT (jerry_value_is_boolean (result));
    TEST_ASSERT (jerry_get_boolean_value (result) == true);
    jerry_release_value (result);
  }

  {
    const char *test_A = "test.my_bool";
    jerry_value_t result = jerry_eval ((const jerry_char_t *) test_A, strlen (test_A), 0);
    TEST_ASSERT (jerry_value_is_boolean (result));
    TEST_ASSERT (jerry_get_boolean_value (result) == true);
    jerry_release_value (result);
  }

  {
    const char *test_A = "test.my_bool_false";
    jerry_value_t result = jerry_eval ((const jerry_char_t *) test_A, strlen (test_A), 0);
    TEST_ASSERT (jerry_value_is_boolean (result));
    TEST_ASSERT (jerry_get_boolean_value (result) == false);
    jerry_release_value (result);
  }

  {
    const char *test_A = "test.my_non_value";
    jerry_value_t result = jerry_eval ((const jerry_char_t *) test_A, strlen (test_A), 0);
    TEST_ASSERT (jerry_value_is_undefined (result));
    jerry_release_value (result);
  }

  {
    const char *test_A = "test.hello(33, 42, 2);";
    jerry_value_t result = jerry_eval ((const jerry_char_t *) test_A, strlen (test_A), 0);
    TEST_ASSERT (jerry_value_is_number (result));
    TEST_ASSERT ((uint32_t) jerry_get_number_value (result) == 3u);
    jerry_release_value (result);
  }

  {
    const char *test_A = "test.hello();";
    jerry_value_t result = jerry_eval ((const jerry_char_t *) test_A, strlen (test_A), 0);
    TEST_ASSERT (jerry_value_is_number (result));
    TEST_ASSERT ((uint32_t) jerry_get_number_value (result) == 0u);
    jerry_release_value (result);
  }

  jerry_cleanup ();
}