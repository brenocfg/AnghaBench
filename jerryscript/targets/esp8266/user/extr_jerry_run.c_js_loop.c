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
typedef  int /*<<< orphan*/  val_args ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 char* fn_sys_loop_name ; 
 int /*<<< orphan*/  jerry_call_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  jerry_create_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_create_string (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_get_global_object () ; 
 int /*<<< orphan*/  jerry_get_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int js_loop (uint32_t ticknow)
{
  jerry_value_t global_obj_val = jerry_get_global_object ();
  jerry_value_t prop_name_val = jerry_create_string ((const jerry_char_t *) fn_sys_loop_name);
  jerry_value_t sysloop_func = jerry_get_property (global_obj_val, prop_name_val);
  jerry_release_value (prop_name_val);

  if (jerry_value_is_error (sysloop_func)) {
    printf ("Error: '%s' not defined!!!\r\n", fn_sys_loop_name);
    jerry_release_value (sysloop_func);
    jerry_release_value (global_obj_val);
    return -1;
  }

  if (!jerry_value_is_function (sysloop_func)) {
    printf ("Error: '%s' is not a function!!!\r\n", fn_sys_loop_name);
    jerry_release_value (sysloop_func);
    jerry_release_value (global_obj_val);
    return -2;
  }

  jerry_value_t val_args[] = { jerry_create_number (ticknow) };
  uint16_t val_argv = sizeof (val_args) / sizeof (jerry_value_t);

  jerry_value_t res = jerry_call_function (sysloop_func,
                                           global_obj_val,
                                           val_args,
                                           val_argv);

  for (uint16_t i = 0; i < val_argv; i++) {
    jerry_release_value (val_args[i]);
  }

  jerry_release_value (sysloop_func);
  jerry_release_value (global_obj_val);

  if (jerry_value_is_error (res)) {
    jerry_release_value (res);
    return -3;
  }

  jerry_release_value (res);

  return 0;
}