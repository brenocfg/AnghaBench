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
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  eval_one (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eval_string1 ; 
 int /*<<< orphan*/  eval_string2 ; 
 int /*<<< orphan*/  eval_string3 ; 
 int /*<<< orphan*/  eval_string4 ; 
 int /*<<< orphan*/  eval_string5 ; 
 int /*<<< orphan*/  eval_string6 ; 
 int /*<<< orphan*/  eval_string7 ; 
 int /*<<< orphan*/  handle_clear_require_cache ; 
 int /*<<< orphan*/  handle_require ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_create_external_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_create_string (int /*<<< orphan*/  const*) ; 
 scalar_t__ jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_global_object () ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_broken_module_register () ; 
 int /*<<< orphan*/  my_custom_module_register () ; 

int
main (int argc, char **argv)
{
  (void) argc;
  (void) argv;
  jerry_value_t js_global = 0, js_function = 0, js_property_name = 0;
  jerry_value_t res;

#ifndef ENABLE_INIT_FINI
  my_broken_module_register ();
  my_custom_module_register ();
#endif /* !ENABLE_INIT_FINI */

  jerry_init (JERRY_INIT_EMPTY);

  js_global = jerry_get_global_object ();

  js_function = jerry_create_external_function (handle_require);
  js_property_name = jerry_create_string ((const jerry_char_t *) "require");
  res = jerry_set_property (js_global, js_property_name, js_function);
  TEST_ASSERT (!jerry_value_is_error (res));
  TEST_ASSERT (jerry_value_is_boolean (res) && jerry_get_boolean_value (res));
  jerry_release_value (res);
  jerry_release_value (js_property_name);
  jerry_release_value (js_function);

  js_function = jerry_create_external_function (handle_clear_require_cache);
  js_property_name = jerry_create_string ((const jerry_char_t *) "clear_require_cache");
  res = jerry_set_property (js_global, js_property_name, js_function);
  TEST_ASSERT (!jerry_value_is_error (res));
  TEST_ASSERT (jerry_value_is_boolean (res) && jerry_get_boolean_value (res));
  jerry_release_value (res);
  jerry_release_value (js_property_name);
  jerry_release_value (js_function);

  jerry_release_value (js_global);

  eval_one (eval_string1, 42);
  eval_one (eval_string2, 29);
  eval_one (eval_string3, 1);
  eval_one (eval_string4, 1);
  eval_one (eval_string5, 1);
  eval_one (eval_string6, 1);
  eval_one (eval_string7, 1);

  jerry_cleanup ();
}