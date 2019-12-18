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
typedef  size_t jerry_size_t ;
typedef  scalar_t__ jerry_char_t ;

/* Variables and functions */
 scalar_t__ balloc (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfree (scalar_t__*) ; 
 size_t jerry_get_utf8_string_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_value_from_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 size_t jerry_string_to_utf8_char_buffer (int /*<<< orphan*/ ,scalar_t__*,size_t) ; 
 scalar_t__ jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,scalar_t__*) ; 

void jerry_resolve_error (jerry_value_t ret_value)
{
  if (jerry_value_is_error (ret_value))
  {
    ret_value = jerry_get_value_from_error (ret_value, true);
    jerry_value_t err_str_val = jerry_value_to_string (ret_value);
    jerry_size_t err_str_size = jerry_get_utf8_string_size (err_str_val);
    jerry_char_t *err_str_buf = (jerry_char_t *) balloc (err_str_size, NULL);
    jerry_size_t sz = jerry_string_to_utf8_char_buffer (err_str_val, err_str_buf, err_str_size);
    err_str_buf[sz] = 0;
    printk ("Script Error: unhandled exception: %s\n", err_str_buf);
    bfree(err_str_buf);
    jerry_release_value (err_str_val);
  }
}