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
typedef  int /*<<< orphan*/  jerry_external_handler_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  jerry_create_external_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_create_string (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_get_global_object () ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_constructor (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_error (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static bool
register_native_function (const char* name,
                          jerry_external_handler_t handler)
{
  jerry_value_t global_obj_val = jerry_get_global_object ();
  jerry_value_t reg_func_val = jerry_create_external_function (handler);
  bool bok = true;

  if (!(jerry_value_is_function (reg_func_val)
        && jerry_value_is_constructor (reg_func_val)))
  {
    printf ("!!! create_external_function failed !!!\r\n");
    jerry_release_value (reg_func_val);
    jerry_release_value (global_obj_val);
    return false;
  }

  jerry_value_t prop_name_val = jerry_create_string ((const jerry_char_t *) name);
  jerry_value_t res = jerry_set_property (global_obj_val, prop_name_val, reg_func_val);

  jerry_release_value (reg_func_val);
  jerry_release_value (global_obj_val);
  jerry_release_value (prop_name_val);

  if (jerry_value_is_error (res))
  {
    printf ("!!! register_native_function failed: [%s]\r\n", name);
    jerry_release_value (res);
    return false;
  }

  jerry_release_value (res);

  return true;
}